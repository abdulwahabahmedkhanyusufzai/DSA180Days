"""
Nexus Resource Allocator — 0/1 Knapsack for Worker Node Packing
================================================================
SOURCE MODULE: 15_Dynamic_Programming (Knapsack sub-folder)

Problem: A worker node has limited RAM (MB) and CPU (millicores).
Each AI task consumes some amount of both.  We must decide WHICH tasks
to assign to a worker so we maximise throughput without crashing the node.

This is the classic 0/1 Knapsack DP problem applied to infrastructure.

Time  : O(n × W × C)  where W = RAM budget, C = CPU budget
Space : O(n × W × C)  — with rolling-array optimisation: O(W × C)
"""

from __future__ import annotations

import logging
from typing import Any, Dict, List, NamedTuple, Tuple

logger = logging.getLogger("nexus.allocator")


class ResourceProfile(NamedTuple):
    task_id:     str
    name:        str
    ram_mb:      int       # RAM required in MB
    cpu_mcores:  int       # CPU required in millicores
    value:       int       # estimated throughput value (higher = prefer)


class WorkerBudget(NamedTuple):
    ram_mb:     int        # total available RAM on this worker
    cpu_mcores: int        # total available CPU on this worker


# ---------------------------------------------------------------------------
# ResourceAllocator
# ---------------------------------------------------------------------------
class ResourceAllocator:
    """
    Given a list of task resource profiles and a worker budget, determine
    the OPTIMAL subset of tasks to assign to the worker.

    Uses 2-D 0/1 Knapsack DP (15_Dynamic_Programming / Knapsack pattern).
    """

    def allocate(
        self, tasks: List[ResourceProfile], budget: WorkerBudget
    ) -> Tuple[List[ResourceProfile], int]:
        """
        Returns (selected_tasks, total_value).

        DP table: dp[i][w][c] = max value using first i tasks,
                                 w MB of RAM, c millicores of CPU.
        Optimised to 2-D rolling array to save memory.
        """
        n   = len(tasks)
        W   = budget.ram_mb
        C   = budget.cpu_mcores

        if n == 0 or W <= 0 or C <= 0:
            return [], 0

        # dp[w][c] = best value achievable with exactly w RAM and c CPU
        dp = [[0] * (C + 1) for _ in range(W + 1)]

        # Track choices for back-tracking selected items
        choices = [[[False] * (C + 1) for _ in range(W + 1)] for _ in range(n)]

        for i, task in enumerate(tasks):
            # Traverse in reverse to avoid re-using the same task (0/1 property)
            new_dp = [row[:] for row in dp]
            for w in range(task.ram_mb, W + 1):
                for c in range(task.cpu_mcores, C + 1):
                    candidate = dp[w - task.ram_mb][c - task.cpu_mcores] + task.value
                    if candidate > new_dp[w][c]:
                        new_dp[w][c] = candidate
                        choices[i][w][c] = True
            dp = new_dp

        # Backtrack to find which tasks were selected
        selected: List[ResourceProfile] = []
        w, c = W, C
        for i in range(n - 1, -1, -1):
            if choices[i][w][c]:
                selected.append(tasks[i])
                w -= tasks[i].ram_mb
                c -= tasks[i].cpu_mcores

        selected.reverse()
        total_value = dp[W][C]

        logger.info(
            f"[Allocator] Selected {len(selected)}/{n} tasks "
            f"(value={total_value}, ram_used={W-w}MB, cpu_used={C-c}mc)"
        )
        return selected, total_value

    def fits(self, task: ResourceProfile, budget: WorkerBudget) -> bool:
        """Quick check: does a single task fit the budget?"""
        return task.ram_mb <= budget.ram_mb and task.cpu_mcores <= budget.cpu_mcores
