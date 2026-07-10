"""
Nexus Trie Router — Python Semantic Intent Router
==================================================
SOURCE MODULE: 10_Trees

Python-side Trie for immediate in-process routing (zero subprocess overhead).
The C++ trie_router binary handles bulk/batch routing for high-throughput paths.
This Python Trie mirrors the exact same insert/prefix-match logic.
"""

from __future__ import annotations

import logging
from typing import Dict, List, Optional, Tuple

logger = logging.getLogger("nexus.trie_router")


class TrieNode:
    __slots__ = ("children", "is_end", "agent_type", "confidence")

    def __init__(self):
        self.children:   Dict[str, "TrieNode"] = {}
        self.is_end:     bool = False
        self.agent_type: str  = ""
        self.confidence: float = 0.0


class TrieRouter:
    """
    10_Trees: Prefix Trie for semantic intent routing.
    Insert keyword → agent mappings, then route prompts via longest-prefix match.
    """

    def __init__(self):
        self._root = TrieNode()
        self._routes: Dict[str, str] = {}

    def insert(self, keyword: str, agent_type: str, confidence: float = 1.0):
        node = self._root
        for ch in keyword.lower():
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end     = True
        node.agent_type = agent_type
        node.confidence = confidence
        self._routes[keyword.lower()] = agent_type
        logger.debug(f"[Trie] Inserted: '{keyword}' → '{agent_type}'")

    def route(self, prompt: str) -> Tuple[str, float]:
        """
        Returns (agent_type, confidence).
        Tries longest prefix match on first token of prompt.
        Falls back to 'default' agent if no match.
        """
        word = prompt.strip().split()[0].lower() if prompt.strip() else ""
        node = self._root
        matched_agent = "default"
        matched_conf  = 0.0

        for ch in word:
            if ch not in node.children:
                break
            node = node.children[ch]
            if node.is_end:
                matched_agent = node.agent_type
                matched_conf  = node.confidence

        return matched_agent, matched_conf

    def load_defaults(self):
        """Pre-load standard AI agent route keywords."""
        defaults = [
            ("extract",   "data_extractor",    1.0),
            ("fetch",     "data_extractor",    1.0),
            ("scrape",    "data_extractor",    0.9),
            ("summarize", "llm_summarizer",    1.0),
            ("summarise", "llm_summarizer",    1.0),
            ("analyze",   "llm_analyzer",      1.0),
            ("analyse",   "llm_analyzer",      1.0),
            ("classify",  "llm_classifier",    1.0),
            ("search",    "search_agent",      1.0),
            ("query",     "db_agent",          1.0),
            ("embed",     "embedding_agent",   1.0),
            ("store",     "db_agent",          1.0),
            ("send",      "notification_agent",1.0),
            ("notify",    "notification_agent",1.0),
            ("validate",  "validator_agent",   1.0),
            ("transform", "transform_agent",   1.0),
        ]
        for kw, agent, conf in defaults:
            self.insert(kw, agent, conf)
        logger.info(f"[Trie] Loaded {len(defaults)} default routes.")

    def all_routes(self) -> Dict[str, str]:
        return dict(self._routes)


# Global singleton
_router = TrieRouter()
_router.load_defaults()


def get_router() -> TrieRouter:
    return _router
