"""
Nexus Rollback Engine — State Backtracking
===========================================
SOURCE MODULES: 12_Backtracking  +  06_Recursion

If an agent hallucinates or crashes mid-workflow, the engine:
  1. Identifies the last 'safe checkpoint' in the DAG (backtracking).
  2. Recursively un-does each downstream task's side-effects.
  3. Restores the system to a known-good state using stored snapshots.

Algorithm mirrors the classic N-Queens / Sudoku Solver backtracking pattern:
  - Explore state → if invalid → restore previous state → try next path.
"""

from __future__ import annotations

import logging
import time
from typing import Any, Callable, Dict, List, Optional

from .dag_engine import DAGWorkflow, TaskNode, TaskState

logger = logging.getLogger("nexus.rollback")


# ---------------------------------------------------------------------------
# Checkpoint — saved state of a completed task
# ---------------------------------------------------------------------------
class Checkpoint:
    def __init__(self, task: TaskNode):
        self.task_id    = task.task_id
        self.name       = task.name
        self.snapshot   = dict(task.snapshot or task.payload)
        self.result     = task.result
        self.saved_at   = time.time()

    def __repr__(self):
        return f"Checkpoint(task_id={self.task_id}, saved_at={self.saved_at:.2f})"


# ---------------------------------------------------------------------------
# RollbackEngine
# ---------------------------------------------------------------------------
class RollbackEngine:
    """
    Maintains a call-stack of Checkpoints (mirroring the recursion call-stack
    from 06_Recursion) and provides O(k) rollback where k = tasks to undo.

    Usage pattern (mirrors backtracking template):
        engine.push_checkpoint(task)        # task succeeded → save state
        ...
        engine.rollback_to(safe_task_id)    # failure → restore
    """

    def __init__(self, undo_fn: Optional[Callable[[str, Dict], None]] = None):
        # Stack of checkpoints — most recent at the end (top of stack)
        self._stack:   List[Checkpoint] = []
        self._index:   Dict[str, int]   = {}    # task_id → stack position
        self._undo_fn  = undo_fn                 # external side-effect reverter

    # -----------------------------------------------------------------------
    # 06_Recursion pattern: push on call, pop on return
    # -----------------------------------------------------------------------
    def push_checkpoint(self, task: TaskNode):
        cp = Checkpoint(task)
        pos = len(self._stack)
        self._stack.append(cp)
        self._index[task.task_id] = pos
        logger.debug(f"[Rollback] Checkpoint saved for '{task.name}' (depth={pos})")

    # -----------------------------------------------------------------------
    # 12_Backtracking: unwind until we reach the safe node
    # -----------------------------------------------------------------------
    def rollback_to(
        self, safe_task_id: str, workflow: DAGWorkflow
    ) -> List[str]:
        """
        Roll back all tasks that ran AFTER safe_task_id.
        Returns list of task_ids that were rolled back.

        Backtracking algorithm:
          while stack top is NOT safe_task_id:
              pop → undo → mark task ROLLED_BACK
        """
        if safe_task_id not in self._index:
            logger.warning(f"[Rollback] Safe task '{safe_task_id}' not in checkpoint stack.")
            return []

        safe_pos = self._index[safe_task_id]
        rolled_back: List[str] = []

        # Pop everything above the safe position (reverse order = correct undo)
        while len(self._stack) > safe_pos + 1:
            cp = self._stack.pop()
            task_id = cp.task_id

            # Undo side effect (if caller registered one)
            if self._undo_fn:
                try:
                    self._undo_fn(task_id, cp.snapshot)
                except Exception as e:
                    logger.error(f"[Rollback] Undo fn failed for {task_id}: {e}")

            # Update the DAG node state
            if task_id in workflow.nodes:
                workflow.nodes[task_id].state = TaskState.ROLLED_BACK

            del self._index[task_id]
            rolled_back.append(task_id)
            logger.info(f"[Rollback] Rolled back task '{cp.name}'")

        logger.info(
            f"[Rollback] Restored to checkpoint '{safe_task_id}'. "
            f"Tasks undone: {rolled_back}"
        )
        return rolled_back

    # -----------------------------------------------------------------------
    # Recursive DFS to find deepest safe ancestor (06_Recursion style)
    # -----------------------------------------------------------------------
    def find_last_safe_ancestor(
        self, failed_task_id: str, workflow: DAGWorkflow
    ) -> Optional[str]:
        """
        Walk parents recursively. Return the deepest ancestor that succeeded.
        """
        def _recurse(tid: str) -> Optional[str]:
            parents = workflow.get_parents(tid)
            if not parents:
                return None
            for parent_id in parents:
                parent_node = workflow.nodes.get(parent_id)
                if parent_node and parent_node.state == TaskState.SUCCESS:
                    return parent_id
                deeper = _recurse(parent_id)
                if deeper:
                    return deeper
            return None

        return _recurse(failed_task_id)

    def checkpoint_count(self) -> int:
        return len(self._stack)

    def clear(self):
        self._stack.clear()
        self._index.clear()
