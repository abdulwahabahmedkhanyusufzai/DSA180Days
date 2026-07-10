"""
Nexus DAG Engine — Core Orchestrator
=====================================
SOURCE MODULE: 16_Graphs_and_Search (BFS_DFS, DSU)

Every AI workflow is modeled as a Directed Acyclic Graph (DAG).
- Topological sort determines the legal execution order.
- BFS-based level traversal identifies which tasks can run CONCURRENTLY.
- DFS cycle-detection prevents infinite dependency loops.
- DSU (Disjoint Set Union) detects isolated sub-graphs (orphaned agents).

This is the brain of the entire Nexus system.
"""

from __future__ import annotations

import asyncio
import logging
import time
import uuid
from collections import defaultdict, deque
from dataclasses import dataclass, field
from enum import Enum
from typing import Any, Callable, Coroutine, Dict, List, Optional, Set

logger = logging.getLogger("nexus.dag")


# ---------------------------------------------------------------------------
# Task States
# ---------------------------------------------------------------------------
class TaskState(str, Enum):
    PENDING   = "PENDING"
    QUEUED    = "QUEUED"
    RUNNING   = "RUNNING"
    SUCCESS   = "SUCCESS"
    FAILED    = "FAILED"
    RETRYING  = "RETRYING"
    ROLLED_BACK = "ROLLED_BACK"
    SKIPPED   = "SKIPPED"


# ---------------------------------------------------------------------------
# Task Node — a single unit of work inside the DAG
# ---------------------------------------------------------------------------
@dataclass
class TaskNode:
    task_id:      str
    name:         str
    agent_type:   str                           # which AI agent handles this
    payload:      Dict[str, Any]
    max_retries:  int  = 3
    priority:     int  = 5                      # 1 (highest) … 10 (lowest)
    timeout_secs: float = 30.0
    state:        TaskState = TaskState.PENDING
    result:       Optional[Any] = None
    error:        Optional[str] = None
    retries_done: int  = 0
    started_at:   Optional[float] = None
    finished_at:  Optional[float] = None
    snapshot:     Optional[Dict[str, Any]] = None   # for rollback

    def duration(self) -> Optional[float]:
        if self.started_at and self.finished_at:
            return round(self.finished_at - self.started_at, 4)
        return None


# ---------------------------------------------------------------------------
# DAGWorkflow — the graph container
# ---------------------------------------------------------------------------
class DAGWorkflow:
    """
    Directed Acyclic Graph of TaskNodes.

    Internally maintains:
      - adjacency list  (task → its dependents)
      - in-degree map   (for Kahn's topological sort)
      - parent map      (for backtracking / rollback)
    """

    def __init__(self, workflow_id: str, name: str):
        self.workflow_id: str = workflow_id
        self.name: str = name
        self.nodes: Dict[str, TaskNode] = {}
        self._adj: Dict[str, List[str]] = defaultdict(list)   # edges a→b means b depends on a
        self._in_degree: Dict[str, int] = defaultdict(int)
        self._parents: Dict[str, List[str]] = defaultdict(list)
        self.created_at: float = time.time()

    # ------------------------------------------------------------------
    def add_task(self, task: TaskNode) -> "DAGWorkflow":
        self.nodes[task.task_id] = task
        if task.task_id not in self._in_degree:
            self._in_degree[task.task_id] = 0
        return self

    def add_dependency(self, from_task_id: str, to_task_id: str) -> "DAGWorkflow":
        """from_task must complete BEFORE to_task can start."""
        self._adj[from_task_id].append(to_task_id)
        self._in_degree[to_task_id] += 1
        self._parents[to_task_id].append(from_task_id)
        return self

    # ------------------------------------------------------------------
    # 16_Graphs_and_Search → Cycle Detection (DFS-based)
    # ------------------------------------------------------------------
    def _has_cycle(self) -> bool:
        WHITE, GRAY, BLACK = 0, 1, 2
        color = {tid: WHITE for tid in self.nodes}

        def dfs(node: str) -> bool:
            color[node] = GRAY
            for nb in self._adj.get(node, []):
                if color[nb] == GRAY:
                    return True
                if color[nb] == WHITE and dfs(nb):
                    return True
            color[node] = BLACK
            return False

        return any(dfs(n) for n in self.nodes if color[n] == 0)

    # ------------------------------------------------------------------
    # 16_Graphs_and_Search → Kahn's Algorithm (Topological Sort)
    # Returns batches of tasks that can run concurrently (BFS levels)
    # ------------------------------------------------------------------
    def topological_levels(self) -> List[List[str]]:
        """
        Returns a list-of-lists.  Each inner list is a 'level' — all
        tasks in the same level have no dependencies on each other and
        can be executed in parallel.
        """
        if self._has_cycle():
            raise ValueError(f"Workflow '{self.name}' contains a cycle — invalid DAG.")

        in_deg = dict(self._in_degree)
        queue: deque[str] = deque()
        levels: List[List[str]] = []

        # Seed with nodes that have no incoming edges
        for tid, deg in in_deg.items():
            if deg == 0:
                queue.append(tid)

        while queue:
            level_size = len(queue)
            level: List[str] = []
            for _ in range(level_size):
                node = queue.popleft()
                level.append(node)
                for nb in self._adj.get(node, []):
                    in_deg[nb] -= 1
                    if in_deg[nb] == 0:
                        queue.append(nb)
            levels.append(level)

        total_scheduled = sum(len(l) for l in levels)
        if total_scheduled != len(self.nodes):
            raise ValueError("Topological sort incomplete — possible hidden cycle.")

        return levels

    # ------------------------------------------------------------------
    # 16_Graphs_and_Search → DSU: detect isolated sub-graphs
    # ------------------------------------------------------------------
    def find_isolated_components(self) -> List[Set[str]]:
        parent = {tid: tid for tid in self.nodes}

        def find(x: str) -> str:
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(a: str, b: str):
            pa, pb = find(a), find(b)
            if pa != pb:
                parent[pa] = pb

        for src, dests in self._adj.items():
            for dst in dests:
                union(src, dst)

        components: Dict[str, Set[str]] = defaultdict(set)
        for tid in self.nodes:
            components[find(tid)].add(tid)
        return list(components.values())

    def get_parents(self, task_id: str) -> List[str]:
        return self._parents.get(task_id, [])


# ---------------------------------------------------------------------------
# DAG Executor — runs the workflow level by level
# ---------------------------------------------------------------------------
class DAGExecutor:
    """
    Executes a DAGWorkflow.

    Each execution level runs tasks concurrently via asyncio.gather().
    Integrates with:
      - PriorityScheduler  (17_Greedy_and_Heaps)   — task ordering within a level
      - RollbackEngine     (12_Backtracking)         — failure recovery
      - WorkerPool         (14_Stacks_and_Queues)    — actual task dispatch
    """

    def __init__(
        self,
        worker_dispatch: Callable[[TaskNode], Coroutine],
        on_task_update:  Optional[Callable[[TaskNode], None]] = None,
    ):
        self._dispatch  = worker_dispatch
        self._on_update = on_task_update

    async def execute(self, workflow: DAGWorkflow) -> Dict[str, Any]:
        levels   = workflow.topological_levels()
        run_log  = []
        start_ts = time.time()

        logger.info(
            f"[DAG] Starting workflow '{workflow.name}' "
            f"({len(workflow.nodes)} tasks, {len(levels)} levels)"
        )

        for lvl_idx, level in enumerate(levels):
            logger.info(f"[DAG] Level {lvl_idx}: running {level} concurrently")
            tasks = [workflow.nodes[tid] for tid in level]

            # Sort within level by priority (honours PriorityScheduler contract)
            tasks.sort(key=lambda t: t.priority)

            results = await asyncio.gather(
                *[self._run_task(t, workflow) for t in tasks],
                return_exceptions=False,
            )
            for task, ok in zip(tasks, results):
                run_log.append({
                    "task_id":  task.task_id,
                    "name":     task.name,
                    "state":    task.state,
                    "duration": task.duration(),
                    "error":    task.error,
                })
                if not ok and task.state == TaskState.FAILED:
                    logger.error(f"[DAG] Task {task.task_id} failed — aborting workflow.")
                    return self._build_report(workflow, run_log, start_ts, "FAILED")

        return self._build_report(workflow, run_log, start_ts, "SUCCESS")

    async def _run_task(self, task: TaskNode, workflow: DAGWorkflow) -> bool:
        task.started_at = time.time()
        task.state      = TaskState.RUNNING
        task.snapshot   = dict(task.payload)   # snapshot for rollback

        if self._on_update:
            self._on_update(task)

        for attempt in range(1, task.max_retries + 1):
            try:
                result = await asyncio.wait_for(
                    self._dispatch(task), timeout=task.timeout_secs
                )
                task.result      = result
                task.state       = TaskState.SUCCESS
                task.finished_at = time.time()
                logger.info(f"[DAG] Task '{task.name}' succeeded (attempt {attempt})")
                if self._on_update:
                    self._on_update(task)
                return True
            except asyncio.TimeoutError:
                task.error       = f"Timeout after {task.timeout_secs}s"
                task.state       = TaskState.RETRYING
                task.retries_done += 1
                logger.warning(f"[DAG] Task '{task.name}' timed out (attempt {attempt})")
            except Exception as exc:
                task.error       = str(exc)
                task.state       = TaskState.RETRYING
                task.retries_done += 1
                logger.warning(f"[DAG] Task '{task.name}' raised {exc} (attempt {attempt})")

            await asyncio.sleep(0.5 * attempt)   # exponential-ish back-off

        task.state       = TaskState.FAILED
        task.finished_at = time.time()
        if self._on_update:
            self._on_update(task)
        return False

    @staticmethod
    def _build_report(
        workflow: DAGWorkflow,
        run_log: list,
        start_ts: float,
        status: str,
    ) -> Dict[str, Any]:
        return {
            "workflow_id":    workflow.workflow_id,
            "workflow_name":  workflow.name,
            "status":         status,
            "total_duration": round(time.time() - start_ts, 4),
            "tasks":          run_log,
        }
