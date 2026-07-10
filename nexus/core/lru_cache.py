"""
Nexus LRU Cache — Cost-Reduction Layer for LLM API Calls
=========================================================
SOURCE MODULES: 13_Linked_List  +  09_Hashing

LLM API calls (OpenAI, Gemini, Anthropic) cost money.
If Agent-B asks "Summarise this document" and Agent-A asked the
same thing 5 minutes ago, we should return the cached answer in O(1).

Implementation:
  - Doubly Linked List (13_Linked_List/LRUCache.cpp pattern)
    maintains recency order: MRU at head, LRU at tail.
  - Hash Map (09_Hashing) provides O(1) key lookup.
  - Eviction: when capacity exceeded, pop tail (LRU item).

This is a production Python port of the exact C++ LRUCache.cpp in the repo.
"""

from __future__ import annotations

import hashlib
import json
import logging
import time
from typing import Any, Dict, Optional

logger = logging.getLogger("nexus.cache")


# ---------------------------------------------------------------------------
# DoublyLinkedList node  (13_Linked_List)
# ---------------------------------------------------------------------------
class _Node:
    __slots__ = ("key", "value", "meta", "hits", "created_at", "prev", "next")

    def __init__(self, key: str, value: Any):
        self.key        = key
        self.value      = value
        self.meta:  Dict = {}
        self.hits:  int  = 0
        self.created_at: float = time.time()
        self.prev: Optional["_Node"] = None
        self.next: Optional["_Node"] = None


# ---------------------------------------------------------------------------
# LRUCache  (13_Linked_List DLL + 09_Hashing unordered_map)
# ---------------------------------------------------------------------------
class LRUCache:
    """
    O(1) get / O(1) put.

    Direct Python port of 13_Linked_List/LRUCache.cpp:
      - head/tail dummy nodes bracket the live list.
      - _cache dict maps key → node (hash map from 09_Hashing).
      - addNode() inserts right after dummy head (MRU position).
      - removeNode() unlinks a node in O(1).
      - moveToHead() = removeNode + addNode.
      - popTail() removes and returns LRU node.
    """

    def __init__(self, capacity: int = 256, ttl_seconds: float = 300.0):
        self._capacity  = capacity
        self._ttl       = ttl_seconds
        self._cache:    Dict[str, _Node] = {}    # 09_Hashing
        self._hits      = 0
        self._misses    = 0

        # 13_Linked_List: dummy sentinel nodes
        self._head = _Node("__HEAD__", None)
        self._tail = _Node("__TAIL__", None)
        self._head.next = self._tail
        self._tail.prev = self._head

    # -----------------------------------------------------------------------
    # Internal DLL operations (13_Linked_List)
    # -----------------------------------------------------------------------
    def _add_node(self, node: _Node):
        """Insert immediately after dummy head (= MRU position)."""
        node.prev = self._head
        node.next = self._head.next
        self._head.next.prev = node
        self._head.next = node

    def _remove_node(self, node: _Node):
        """Unlink node in O(1)."""
        node.prev.next = node.next
        node.next.prev = node.prev

    def _move_to_head(self, node: _Node):
        self._remove_node(node)
        self._add_node(node)

    def _pop_tail(self) -> _Node:
        lru = self._tail.prev
        self._remove_node(lru)
        return lru

    # -----------------------------------------------------------------------
    # Public API
    # -----------------------------------------------------------------------
    def get(self, key: str) -> Optional[Any]:
        node = self._cache.get(key)
        if node is None:
            self._misses += 1
            return None
        # TTL check
        if self._ttl and (time.time() - node.created_at) > self._ttl:
            self._evict(node)
            self._misses += 1
            logger.debug(f"[Cache] EXPIRED: {key}")
            return None
        self._move_to_head(node)
        node.hits += 1
        self._hits += 1
        logger.debug(f"[Cache] HIT: {key} (hits={node.hits})")
        return node.value

    def put(self, key: str, value: Any, meta: Optional[Dict] = None) -> None:
        node = self._cache.get(key)
        if node:
            node.value      = value
            node.meta       = meta or {}
            node.created_at = time.time()
            self._move_to_head(node)
        else:
            new_node = _Node(key, value)
            new_node.meta = meta or {}
            self._cache[key] = new_node
            self._add_node(new_node)
            if len(self._cache) > self._capacity:
                lru = self._pop_tail()
                del self._cache[lru.key]
                logger.debug(f"[Cache] EVICT: {lru.key}")
        logger.debug(f"[Cache] PUT: {key}")

    def _evict(self, node: _Node):
        self._remove_node(node)
        del self._cache[node.key]

    def invalidate(self, key: str) -> bool:
        node = self._cache.get(key)
        if node:
            self._evict(node)
            return True
        return False

    def clear(self):
        self._cache.clear()
        self._head.next = self._tail
        self._tail.prev = self._head

    # -----------------------------------------------------------------------
    # Utility: canonical cache key from prompt + model
    # -----------------------------------------------------------------------
    @staticmethod
    def make_key(agent_type: str, payload: Dict) -> str:
        """
        09_Hashing: deterministic SHA-256 fingerprint of the request.
        Agents with identical (agent_type, payload) share the same cache key.
        """
        raw = json.dumps({"agent": agent_type, "payload": payload}, sort_keys=True)
        return hashlib.sha256(raw.encode()).hexdigest()[:32]

    # -----------------------------------------------------------------------
    # Stats
    # -----------------------------------------------------------------------
    @property
    def hit_rate(self) -> float:
        total = self._hits + self._misses
        return round(self._hits / total, 4) if total else 0.0

    def stats(self) -> Dict:
        return {
            "size":      len(self._cache),
            "capacity":  self._capacity,
            "hits":      self._hits,
            "misses":    self._misses,
            "hit_rate":  self.hit_rate,
            "ttl_secs":  self._ttl,
        }
