"""
Nexus C++ Services — Python API wrappers over compiled C++ binaries
====================================================================
Each function compiles (once) and calls the real C++ binary via subprocess.
This is what makes the system ACTUALLY USE the 18 folders of C++ code.
"""

from __future__ import annotations

import logging
import os
import time
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

from .cpp_bridge import call_cpp, compile_all, get_binary

logger = logging.getLogger("nexus.services")

# ---------------------------------------------------------------------------
# 1. LRU CACHE SERVICE  (13_Linked_List/LRUCache.cpp)
# ---------------------------------------------------------------------------
def lru_cache_get(key: int) -> Dict:
    """Call the real C++ LRU cache binary for a GET operation."""
    import json
    bin_path = get_binary("lru_cache")
    if not bin_path:
        return {"ok": False, "error": "lru_cache binary not available"}
    stdin = json.dumps({"op": "get", "key": key}) + "\n"
    return call_cpp(bin_path, stdin)

def lru_cache_put(key: int, value: int) -> Dict:
    """Call the real C++ LRU cache binary for a PUT operation."""
    import json
    bin_path = get_binary("lru_cache")
    if not bin_path:
        return {"ok": False, "error": "lru_cache binary not available"}
    stdin = json.dumps({"op": "put", "key": key, "value": value}) + "\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# 2. PRIORITY SCHEDULER  (17_Greedy_and_Heaps/MinimumCosttoHire.cpp)
# ---------------------------------------------------------------------------
def schedule_tasks_greedy(
    tasks: List[Dict],   # each: {id, name, priority, quality, wage}
    top_k: int,
) -> Dict:
    """
    Call the C++ greedy scheduler using MinimumCosttoHire.cpp heap logic.
    Returns ordered task IDs for the top_k highest-priority slots.
    """
    bin_path = get_binary("priority_scheduler")
    if not bin_path:
        return {"ok": False, "error": "priority_scheduler binary not available"}

    n = len(tasks)
    lines = [f"{n} {top_k}"]
    for t in tasks:
        q  = int(t.get("quality", t.get("priority", 5)))
        w  = int(t.get("wage",    t.get("priority", 5) * 2))
        lines.append(f"{q} {w}")
    for t in tasks:
        lines.append(str(t["id"]))
    stdin = "\n".join(lines) + "\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# 3. PRIME KEY GENERATOR  (02_Math_and_Numbers/Primes/primeNumber.cpp)
# ---------------------------------------------------------------------------
def generate_api_key(seed: int = 1000, count: int = 8) -> Dict:
    """
    Generate API key material using the prime checker from 02_Math_and_Numbers.
    Returns a list of prime numbers as key components.
    """
    bin_path = get_binary("prime_keygen")
    if not bin_path:
        return {"ok": False, "error": "prime_keygen binary not available"}

    stdin = f"{seed} {count}\n"
    result = call_cpp(bin_path, stdin)
    if result["ok"]:
        primes = result.get("output", {}).get("primes", [])
        # Assemble into a hex-like API key string
        key = "-".join(f"{p:04X}" for p in primes)
        result["api_key"] = key
    return result


# ---------------------------------------------------------------------------
# 4. RBAC BITMASK  (08_Bit_Manipulation/Basics/DividetheInteger.cpp)
# ---------------------------------------------------------------------------
PERM_READ    = 1
PERM_WRITE   = 2
PERM_EXECUTE = 4
PERM_DELETE  = 8
PERM_ADMIN   = 16

def rbac_check(role_mask: int, permission_bit: int) -> Dict:
    bin_path = get_binary("rbac_bitmask")
    if not bin_path:
        return {"ok": False, "error": "rbac_bitmask binary not available"}
    stdin = f"CHECK {role_mask} {permission_bit}\n"
    return call_cpp(bin_path, stdin)

def rbac_describe(role_mask: int) -> Dict:
    bin_path = get_binary("rbac_bitmask")
    if not bin_path:
        return {"ok": False, "error": "rbac_bitmask binary not available"}
    stdin = f"DESCRIBE {role_mask}\n"
    return call_cpp(bin_path, stdin)

def rbac_grant(role_mask: int, permission_bit: int) -> Dict:
    bin_path = get_binary("rbac_bitmask")
    if not bin_path:
        return {"ok": False, "error": "rbac_bitmask binary not available"}
    stdin = f"GRANT {role_mask} {permission_bit}\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# 5. LOG SORT + BINARY SEARCH  (07_Sorting + 11_Binary_Search)
# ---------------------------------------------------------------------------
def sort_and_find_log(
    logs: List[Dict],     # each: {timestamp_ms: int, event_type: str}
    target_ts: int,
) -> Dict:
    """
    Sort logs using 07_Sorting pattern, then binary-search for target_ts
    using 11_Binary_Search. Finds exact crash millisecond.
    """
    bin_path = get_binary("log_sort_search")
    if not bin_path:
        return {"ok": False, "error": "log_sort_search binary not available"}

    n = len(logs)
    lines = [str(n)]
    for log in logs:
        lines.append(f"{log['timestamp_ms']} {log['event_type']}")
    lines.append(str(target_ts))
    stdin = "\n".join(lines) + "\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# 6. DAG TOPOLOGY  (16_Graphs_and_Search BFS + DSU)
# ---------------------------------------------------------------------------
def compute_dag_levels(
    task_ids: List[str],
    edges: List[Tuple[int, int]],   # (from_idx, to_idx) — 0-based indices
) -> Dict:
    """
    Runs the real C++ DAG topological sort using BFS (ShortestPathInGrid.cpp)
    and DSU (SimilarStringGroups.cpp) from 16_Graphs_and_Search.
    Returns execution levels for parallel scheduling.
    """
    bin_path = get_binary("dag_topology")
    if not bin_path:
        return {"ok": False, "error": "dag_topology binary not available"}

    N = len(task_ids)
    M = len(edges)
    lines = [f"{N} {M}"]
    for f, t in edges:
        lines.append(f"{f} {t}")
    for tid in task_ids:
        lines.append(str(tid))
    stdin = "\n".join(lines) + "\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# 7. KNAPSACK ALLOCATOR  (15_Dynamic_Programming/Knapsack)
# ---------------------------------------------------------------------------
def allocate_tasks_knapsack(
    tasks: List[Dict],    # each: {id, ram_mb, cpu_mcores, value}
    ram_budget: int,
    cpu_budget: int,
) -> Dict:
    """
    Uses the real C++ ProfitableSchemas.cpp DP pattern to solve the
    2D 0/1 knapsack and return optimal task subset for a worker node.
    """
    bin_path = get_binary("knapsack_allocator")
    if not bin_path:
        return {"ok": False, "error": "knapsack_allocator binary not available"}

    N = len(tasks)
    lines = [f"{N} {ram_budget} {cpu_budget}"]
    for t in tasks:
        lines.append(f"{t['id']} {t['ram_mb']} {t['cpu_mcores']} {t['value']}")
    stdin = "\n".join(lines) + "\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# 8. SLIDING WINDOW RATE LIMITER  (05_Two_Pointers)
# ---------------------------------------------------------------------------
def check_rate_limit(
    events: List[Dict],   # each: {timestamp_ms, tokens}
    limit: int,
    query_ts: int,
) -> Dict:
    """
    Uses the deque sliding-window from ShortestSubarraywithSumofK.cpp
    to check if token usage in the last 60s exceeds the limit.
    """
    bin_path = get_binary("sliding_window_rate")
    if not bin_path:
        return {"ok": False, "error": "sliding_window_rate binary not available"}

    lines = [str(limit)]
    for e in events:
        lines.append(f"{e['timestamp_ms']} {e['tokens']}")
    lines.append(f"QUERY {query_ts}")
    stdin = "\n".join(lines) + "\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# 9. ANALYTICS SEGMENT  (18_Advanced_Data_Structures/fallingSquares.cpp)
# ---------------------------------------------------------------------------
def analytics_range_query(
    events: List[Dict],   # each: {time_bucket, tokens}
    t_start: int,
    t_end: int,
) -> Dict:
    """
    Queries total token usage over a time range using fallingSquares.cpp
    coordinate-compression interval pattern.
    """
    bin_path = get_binary("analytics_segment")
    if not bin_path:
        return {"ok": False, "error": "analytics_segment binary not available"}

    N = len(events)
    lines = [str(N)]
    for e in events:
        lines.append(f"{e['time_bucket']} {e['tokens']}")
    lines.append(f"RANGE {t_start} {t_end}")
    stdin = "\n".join(lines) + "\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# 10. PAYLOAD PARSER  (04_Strings Z-algo + 03_Arrays Prefix Sum)
# ---------------------------------------------------------------------------
def parse_payload(pattern: str, text: str) -> Dict:
    """
    Scans LLM output for forbidden patterns using Z-algorithm (04_Strings)
    and counts tokens using prefix-sum technique (03_Arrays).
    """
    bin_path = get_binary("payload_parser")
    if not bin_path:
        return {"ok": False, "error": "payload_parser binary not available"}

    stdin = f"{pattern}\n{text}\n"
    return call_cpp(bin_path, stdin, timeout=10.0)


# ---------------------------------------------------------------------------
# 11. TRIE ROUTER  (10_Trees + 04_Strings PrefixandSuffixSearch)
# ---------------------------------------------------------------------------
def route_prompt(
    routes: List[Dict],   # each: {keyword, agent}
    prompt_word: str,
) -> Dict:
    """
    Uses the Trie (10_Trees) with longest-prefix matching from
    PrefixandSuffixSearch.cpp to route prompt to the correct agent.
    """
    bin_path = get_binary("trie_router")
    if not bin_path:
        return {"ok": False, "error": "trie_router binary not available"}

    lines = []
    for r in routes:
        lines.append(f"INSERT {r['keyword']} {r['agent']}")
    lines.append(f"ROUTE {prompt_word}")
    lines.append("END")
    stdin = "\n".join(lines) + "\n"
    result = call_cpp(bin_path, stdin)
    # Parse the last line (the ROUTE response)
    if result["ok"] and isinstance(result.get("raw"), str):
        import json
        json_lines = [l for l in result["raw"].strip().split("\n") if l.strip()]
        for line in reversed(json_lines):
            try:
                data = json.loads(line)
                if data.get("op") == "ROUTE":
                    return {"ok": True, **data}
            except Exception:
                pass
    return result


# ---------------------------------------------------------------------------
# 12. ROLLBACK SUM VALIDATOR  (06_Recursion + 12_Backtracking)
# ---------------------------------------------------------------------------
def validate_rollback_checksum(values: List[int], expected_sum: int) -> Dict:
    """
    Uses the recursive sum from SumofFirstNnumbers.cpp (06_Recursion)
    to verify a checkpoint's integrity before rollback (12_Backtracking).
    """
    bin_path = get_binary("rollback_sum")
    if not bin_path:
        return {"ok": False, "error": "rollback_sum binary not available"}

    N = len(values)
    lines = [str(N)] + [str(v) for v in values] + [str(expected_sum)]
    stdin = "\n".join(lines) + "\n"
    return call_cpp(bin_path, stdin)


# ---------------------------------------------------------------------------
# Bootstrap: compile all runners at import time (non-blocking attempt)
# ---------------------------------------------------------------------------
def bootstrap_cpp_modules() -> Dict[str, bool]:
    """Compile all C++ runners. Call this at server startup."""
    logger.info("[Services] Bootstrapping C++ modules...")
    results = compile_all()
    ok_count = sum(1 for v in results.values() if v)
    logger.info(f"[Services] Compiled {ok_count}/{len(results)} modules: {results}")
    return results
