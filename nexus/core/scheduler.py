"""
Nexus Priority Scheduler — Task Queue & Load Balancer
======================================================
SOURCE MODULES: 14_Stacks_and_Queues  +  17_Greedy_and_Heaps

Architecture:
  - A min-heap (priority queue) from 17_Greedy_and_Heaps sorts incoming tasks
    so VIP / critical jobs jump the queue in O(log n).
  - A concurrent worker pool from 14_Stacks_and_Queues dispatches tasks
    to background coroutines (mirrors Monotonic Stack discipline for ordering).
  - A Greedy scheduling policy assigns tasks to the first available worker
    that satisfies the resource budget (CPU + RAM).
"""

from __future__ import annotations

import asyncio
import heapq
import logging
import time
import uuid
from dataclasses import dataclass, field
from typing import Any, Callable, Coroutine, Dict, List, Optional, Tuple

logger = logging.getLogger("nexus.scheduler")


# ---------------------------------------------------------------------------
# PriorityEntry — wrapper so TaskNode can live in a min-heap
# ---------------------------------------------------------------------------
@dataclass(order=True)
class PriorityEntry:
    priority:   int              # lower = more urgent (1 is highest)
    timestamp:  float            # tie-break: earlier submission wins
    entry_id:   str = field(compare=False)
    payload:    Any = field(compare=False)   # the TaskNode

    @classmethod
    def from_task(cls, task) -> "PriorityEntry":
        return cls(
            priority  = task.priority,
            timestamp = time.time(),
            entry_id  = task.task_id,
            payload   = task,
        )


# ---------------------------------------------------------------------------
# PriorityScheduler  (17_Greedy_and_Heaps)
# ---------------------------------------------------------------------------
class PriorityScheduler:
    """
    O(log n) insert / O(log n) pop-min.

    Internally a Python min-heap (heapq).  Mirrors the 'MinimumCosttoHire'
    greedy pattern: always pick the task with least cost (highest priority).
    """

    def __init__(self):
        self._heap:  List[PriorityEntry] = []
        self._count: int = 0

    def push(self, task) -> None:
        entry = PriorityEntry.from_task(task)
        heapq.heappush(self._heap, entry)
        self._count += 1
        logger.debug(f"[Scheduler] Enqueued '{task.name}' (priority={task.priority})")

    def pop(self) -> Optional[Any]:
        if not self._heap:
            return None
        entry = heapq.heappop(self._heap)
        self._count -= 1
        logger.debug(f"[Scheduler] Dequeued '{entry.payload.name}'")
        return entry.payload

    def peek(self) -> Optional[Any]:
        return self._heap[0].payload if self._heap else None

    def __len__(self) -> int:
        return self._count

    def is_empty(self) -> bool:
        return self._count == 0

    # Heap-sort to get ordered snapshot (non-destructive) — 17_Greedy_and_Heaps
    def ordered_snapshot(self) -> List[Any]:
        return [e.payload for e in sorted(self._heap)]


# ---------------------------------------------------------------------------
# WorkerPool  (14_Stacks_and_Queues)
# ---------------------------------------------------------------------------
class WorkerPool:
    """
    Manages N concurrent async workers.

    Internally uses asyncio.Queue (a FIFO) from 14_Stacks_and_Queues.
    Workers sit in a blocking loop dequeuing tasks — identical to the
    'ImplementQueueusingStack' pattern but with true async semantics.

    A monotonic-stack discipline ensures no worker is double-assigned
    (each item is consumed exactly once).
    """

    def __init__(
        self,
        worker_count: int,
        dispatch_fn: Callable[[Any], Coroutine],
        on_complete:  Optional[Callable[[Any, Any], None]] = None,
    ):
        self._queue:       asyncio.Queue = asyncio.Queue()
        self._workers:     List[asyncio.Task] = []
        self._dispatch_fn  = dispatch_fn
        self._on_complete  = on_complete
        self._worker_count = worker_count
        self._active:      int = 0
        self._running:     bool = False

    async def start(self):
        self._running = True
        for i in range(self._worker_count):
            worker = asyncio.create_task(self._worker_loop(i))
            self._workers.append(worker)
        logger.info(f"[WorkerPool] Started {self._worker_count} workers.")

    async def stop(self):
        self._running = False
        # Poison pills — one per worker
        for _ in self._workers:
            await self._queue.put(None)
        await asyncio.gather(*self._workers, return_exceptions=True)
        logger.info("[WorkerPool] All workers stopped.")

    async def submit(self, task) -> None:
        await self._queue.put(task)
        logger.debug(f"[WorkerPool] Task '{task.name}' added to queue (qsize={self._queue.qsize()})")

    async def _worker_loop(self, worker_id: int):
        """
        Classic consumer loop — 14_Stacks_and_Queues pattern.
        Drain the queue until a None sentinel is received.
        """
        while True:
            task = await self._queue.get()
            if task is None:
                break
            self._active += 1
            logger.debug(f"[Worker-{worker_id}] Picked up '{task.name}'")
            try:
                result = await self._dispatch_fn(task)
                if self._on_complete:
                    self._on_complete(task, result)
            except Exception as exc:
                logger.error(f"[Worker-{worker_id}] Error on '{task.name}': {exc}")
            finally:
                self._active -= 1
                self._queue.task_done()

    @property
    def active_count(self) -> int:
        return self._active

    @property
    def pending_count(self) -> int:
        return self._queue.qsize()
