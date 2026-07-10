"""
Nexus FastAPI Server — The API Gateway
======================================
POST /execute-workflow   — Submit a DAG workflow for execution
POST /route-prompt       — Route a prompt to the correct AI agent (Trie)
POST /rbac/check         — Check permissions (bitmask from 08_Bit_Manipulation)
POST /rbac/grant         — Grant a permission
GET  /keygen             — Generate API key (prime numbers from 02_Math)
POST /logs/search        — Sort logs + binary search (07_Sorting + 11_BinarySearch)
POST /cache/get          — LRU cache GET (13_Linked_List + 09_Hashing)
POST /cache/put          — LRU cache PUT
POST /allocate           — Knapsack resource allocation (15_DP)
POST /analytics/range    — Token usage analytics (18_Advanced_DS)
POST /parse-payload      — Z-algo payload scanner (04_Strings + 03_Arrays)
GET  /health             — System health + module status
GET  /compile            — Recompile all C++ modules
"""

from __future__ import annotations

import asyncio
import logging
import time
import uuid
from typing import Any, Dict, List, Optional

import uvicorn
from fastapi import FastAPI, HTTPException, Request
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse
from pydantic import BaseModel, Field

from nexus.cpp_services import (
    analytics_range_query,
    allocate_tasks_knapsack,
    bootstrap_cpp_modules,
    check_rate_limit,
    compute_dag_levels,
    generate_api_key,
    lru_cache_get,
    lru_cache_put,
    parse_payload,
    rbac_check,
    rbac_describe,
    rbac_grant,
    route_prompt,
    sort_and_find_log,
    validate_rollback_checksum,
)
from nexus.core.dag_engine import DAGWorkflow, DAGExecutor, TaskNode, TaskState
from nexus.core.trie_router import get_router

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(name)s: %(message)s",
)
logger = logging.getLogger("nexus.server")

# ---------------------------------------------------------------------------
# App Setup
# ---------------------------------------------------------------------------
app = FastAPI(
    title="Nexus DAG Engine",
    description=(
        "Autonomous AI-Agent Orchestration Engine\n\n"
        "Utilises all 18 DSA folders as compiled C++ algorithm modules.\n"
        "A lightweight, high-performance alternative to Apache Airflow / LangGraph."
    ),
    version="1.0.0",
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)

# Module compile status (populated at startup)
_module_status: Dict[str, bool] = {}

# ---------------------------------------------------------------------------
# Pydantic Models
# ---------------------------------------------------------------------------
class TaskDef(BaseModel):
    id:           str
    name:         str
    agent_type:   str
    payload:      Dict[str, Any] = {}
    priority:     int = Field(default=5, ge=1, le=10)
    max_retries:  int = Field(default=3, ge=0, le=10)
    timeout_secs: float = Field(default=30.0)
    ram_mb:       int = Field(default=128)
    cpu_mcores:   int = Field(default=500)
    wage:         int = Field(default=10)
    quality:      int = Field(default=5)

class EdgeDef(BaseModel):
    from_task: str
    to_task:   str

class WorkflowRequest(BaseModel):
    name:     str
    tasks:    List[TaskDef]
    edges:    List[EdgeDef] = []
    dry_run:  bool = False   # if True, only compute topology — don't execute

class RoutePromptRequest(BaseModel):
    prompt:  str
    use_cpp: bool = True   # True = call C++ trie binary; False = Python trie

class RBACRequest(BaseModel):
    role_mask:      int
    permission_bit: Optional[int] = None

class LogEntry(BaseModel):
    timestamp_ms: int
    event_type:   str

class LogSearchRequest(BaseModel):
    logs:      List[LogEntry]
    target_ts: int

class CacheGetRequest(BaseModel):
    key: int

class CachePutRequest(BaseModel):
    key:   int
    value: int

class AllocateRequest(BaseModel):
    tasks:      List[TaskDef]
    ram_budget: int = 4096
    cpu_budget: int = 8000

class RateCheckRequest(BaseModel):
    events:   List[Dict[str, int]]   # [{timestamp_ms, tokens}]
    limit:    int = 90000
    query_ts: int

class AnalyticsRequest(BaseModel):
    events:  List[Dict[str, int]]   # [{time_bucket, tokens}]
    t_start: int
    t_end:   int

class ParsePayloadRequest(BaseModel):
    pattern: str
    text:    str

class RollbackValidateRequest(BaseModel):
    values:       List[int]
    expected_sum: int

# ---------------------------------------------------------------------------
# Startup / Shutdown
# ---------------------------------------------------------------------------
@app.on_event("startup")
async def on_startup():
    global _module_status
    logger.info("🚀 Nexus DAG Engine starting up...")
    # Compile C++ modules in background thread (non-blocking)
    loop = asyncio.get_event_loop()
    _module_status = await loop.run_in_executor(None, bootstrap_cpp_modules)
    ok = sum(1 for v in _module_status.values() if v)
    logger.info(f"✅ {ok}/{len(_module_status)} C++ modules compiled.")

# ---------------------------------------------------------------------------
# Health Check
# ---------------------------------------------------------------------------
@app.get("/health", tags=["System"])
async def health():
    return {
        "status":         "ok",
        "engine":         "Nexus DAG Engine v1.0.0",
        "cpp_modules":    _module_status,
        "modules_ok":     sum(1 for v in _module_status.values() if v),
        "modules_total":  len(_module_status),
        "timestamp":      time.time(),
        "dsa_folders_used": [
            "01_Basics → latency math",
            "02_Math_and_Numbers → prime key generation",
            "03_Arrays → prefix sum token counting",
            "04_Strings → Z-algo payload scanning",
            "05_Two_Pointers → sliding window rate limiter",
            "06_Recursion → recursive rollback checksum",
            "07_Sorting → log timestamp sorting",
            "08_Bit_Manipulation → RBAC bitmask permissions",
            "09_Hashing → LRU cache hash map",
            "10_Trees → Trie semantic routing",
            "11_Binary_Search → log crash finder",
            "12_Backtracking → state rollback engine",
            "13_Linked_List → LRU cache doubly-linked list",
            "14_Stacks_and_Queues → worker pool queue",
            "15_Dynamic_Programming → knapsack resource allocator",
            "16_Graphs_and_Search → DAG BFS topology + DSU",
            "17_Greedy_and_Heaps → priority heap scheduler",
            "18_Advanced_Data_Structures → segment analytics",
        ],
    }

@app.get("/compile", tags=["System"])
async def recompile():
    global _module_status
    loop = asyncio.get_event_loop()
    _module_status = await loop.run_in_executor(None, bootstrap_cpp_modules)
    return {"status": "done", "results": _module_status}

# ---------------------------------------------------------------------------
# POST /execute-workflow   [CORE ENDPOINT]
# 16_Graphs, 17_Heaps, 15_DP, 12_Backtracking, 14_Queues
# ---------------------------------------------------------------------------
@app.post("/execute-workflow", tags=["Orchestration"])
async def execute_workflow(req: WorkflowRequest):
    workflow_id = str(uuid.uuid4())[:8]
    start_ts    = time.time()

    # ── Step 1: Compute DAG topology via REAL C++ binary (16_Graphs + DSU) ─
    task_ids = [t.id for t in req.tasks]
    # Build index map for edges
    id_to_idx = {t.id: i for i, t in enumerate(req.tasks)}
    edge_tuples = []
    for e in req.edges:
        if e.from_task in id_to_idx and e.to_task in id_to_idx:
            edge_tuples.append((id_to_idx[e.from_task], id_to_idx[e.to_task]))

    topology = compute_dag_levels(task_ids, edge_tuples)   # C++ call ↑

    if not topology.get("ok"):
        raise HTTPException(400, detail=f"DAG error: {topology.get('error')}")
    if topology.get("output", {}).get("has_cycle"):
        raise HTTPException(400, detail="Workflow contains a dependency cycle.")

    levels = topology.get("output", {}).get("levels", [[t.id for t in req.tasks]])

    # ── Step 2: Greedy priority scheduling within each level (17_Heaps) ────
    task_map = {t.id: t for t in req.tasks}
    scheduled_order = []
    for level in levels:
        level_tasks = [task_map[tid] for tid in level if tid in task_map]
        if len(level_tasks) > 1:
            # Call C++ greedy scheduler
            sched = schedule_tasks_greedy(
                [{"id": t.id, "quality": t.quality, "wage": t.wage} for t in level_tasks],
                top_k=len(level_tasks),
            )
            if sched.get("ok") and isinstance(sched.get("output"), dict):
                ordered_ids = sched["output"].get("scheduled", level)
            else:
                ordered_ids = sorted(level, key=lambda tid: task_map[tid].priority)
        else:
            ordered_ids = [t.id for t in level_tasks]
        scheduled_order.append(ordered_ids)

    # ── Step 3: Knapsack resource allocation (15_DP) ───────────────────────
    all_tasks_flat = [t for t in req.tasks]
    allocation = allocate_tasks_knapsack(
        [{"id": t.id, "ram_mb": t.ram_mb, "cpu_mcores": t.cpu_mcores, "value": 10 - t.priority} for t in all_tasks_flat],
        ram_budget=4096,
        cpu_budget=8000,
    )

    if req.dry_run:
        return {
            "workflow_id":       workflow_id,
            "dry_run":           True,
            "topology":          levels,
            "scheduled_order":   scheduled_order,
            "allocation":        allocation.get("output", {}),
            "has_cycle":         topology.get("output", {}).get("has_cycle", False),
            "task_count":        len(req.tasks),
            "compute_time_ms":   round((time.time() - start_ts) * 1000, 2),
        }

    # ── Step 4: Execute via Python DAG engine (uses worker queue from 14) ──
    dag = DAGWorkflow(workflow_id=workflow_id, name=req.name)
    for t in req.tasks:
        dag.add_task(TaskNode(
            task_id=t.id, name=t.name, agent_type=t.agent_type,
            payload=t.payload, priority=t.priority,
            max_retries=t.max_retries, timeout_secs=t.timeout_secs,
        ))
    for e in req.edges:
        dag.add_dependency(e.from_task, e.to_task)

    async def mock_dispatch(task: TaskNode):
        """Simulated agent execution — replace with real agent calls."""
        await asyncio.sleep(0.05)
        return {"agent": task.agent_type, "status": "executed", "task": task.name}

    executor = DAGExecutor(worker_dispatch=mock_dispatch)
    result   = await executor.execute(dag)

    result["workflow_id"]     = workflow_id
    result["scheduled_order"] = scheduled_order
    result["allocation"]      = allocation.get("output", {})
    result["topology_levels"] = levels
    result["compute_time_ms"] = round((time.time() - start_ts) * 1000, 2)
    return result


# ---------------------------------------------------------------------------
# POST /route-prompt  (10_Trees Trie + 04_Strings)
# ---------------------------------------------------------------------------
@app.post("/route-prompt", tags=["Routing"])
async def route_prompt_endpoint(req: RoutePromptRequest):
    router = get_router()

    if req.use_cpp:
        # Use C++ trie binary
        routes = [{"keyword": kw, "agent": ag} for kw, ag in router.all_routes().items()]
        first_word = req.prompt.strip().split()[0] if req.prompt.strip() else ""
        result = route_prompt(routes, first_word)
        cpp_output = result.get("output") or result
        return {
            "prompt":      req.prompt,
            "engine":      "C++ Trie (10_Trees)",
            "agent":       cpp_output.get("agent", "default"),
            "keyword":     cpp_output.get("keyword"),
            "confidence":  cpp_output.get("confidence", 0.0),
        }
    else:
        # Python Trie (same algorithm, in-process)
        agent, conf = router.route(req.prompt)
        return {
            "prompt":     req.prompt,
            "engine":     "Python Trie (10_Trees)",
            "agent":      agent,
            "confidence": conf,
        }


# ---------------------------------------------------------------------------
# POST /rbac/check  (08_Bit_Manipulation)
# ---------------------------------------------------------------------------
@app.post("/rbac/check", tags=["Security"])
async def rbac_check_endpoint(req: RBACRequest):
    if req.permission_bit is None:
        result = rbac_describe(req.role_mask)
    else:
        result = rbac_check(req.role_mask, req.permission_bit)
    return {"source": "08_Bit_Manipulation/DividetheInteger.cpp (bit-shift pattern)", **result}

@app.post("/rbac/grant", tags=["Security"])
async def rbac_grant_endpoint(req: RBACRequest):
    if req.permission_bit is None:
        raise HTTPException(400, "permission_bit required for GRANT")
    result = rbac_grant(req.role_mask, req.permission_bit)
    return {"source": "08_Bit_Manipulation", **result}


# ---------------------------------------------------------------------------
# GET /keygen  (02_Math_and_Numbers/Primes + 01_Basics)
# ---------------------------------------------------------------------------
@app.get("/keygen", tags=["Security"])
async def keygen(seed: int = 1000, count: int = 8):
    result = generate_api_key(seed=seed, count=count)
    return {
        "source":   "02_Math_and_Numbers/Primes/primeNumber.cpp",
        "api_key":  result.get("api_key"),
        "primes":   result.get("output", {}).get("primes") if isinstance(result.get("output"), dict) else None,
        "latency_math_source": "01_Basics/Basic_Operations/calculator.cpp",
    }


# ---------------------------------------------------------------------------
# POST /logs/search  (07_Sorting + 11_Binary_Search)
# ---------------------------------------------------------------------------
@app.post("/logs/search", tags=["Observability"])
async def log_search(req: LogSearchRequest):
    logs = [{"timestamp_ms": l.timestamp_ms, "event_type": l.event_type} for l in req.logs]
    result = sort_and_find_log(logs, req.target_ts)
    return {
        "source":  "07_Sorting/ArrayPartition.cpp + 11_Binary_Search",
        **result,
    }


# ---------------------------------------------------------------------------
# POST /cache/get and /cache/put  (13_Linked_List + 09_Hashing)
# ---------------------------------------------------------------------------
@app.post("/cache/get", tags=["Cache"])
async def cache_get(req: CacheGetRequest):
    result = lru_cache_get(req.key)
    return {"source": "13_Linked_List/LRUCache.cpp + 09_Hashing", **result}

@app.post("/cache/put", tags=["Cache"])
async def cache_put(req: CachePutRequest):
    result = lru_cache_put(req.key, req.value)
    return {"source": "13_Linked_List/LRUCache.cpp + 09_Hashing", **result}


# ---------------------------------------------------------------------------
# POST /allocate  (15_Dynamic_Programming/Knapsack)
# ---------------------------------------------------------------------------
@app.post("/allocate", tags=["Resources"])
async def allocate(req: AllocateRequest):
    tasks = [
        {"id": t.id, "ram_mb": t.ram_mb, "cpu_mcores": t.cpu_mcores, "value": 10 - t.priority}
        for t in req.tasks
    ]
    result = allocate_tasks_knapsack(tasks, req.ram_budget, req.cpu_budget)
    return {
        "source": "15_Dynamic_Programming/Knapsack/ProfitableSchemas.cpp",
        **result,
    }


# ---------------------------------------------------------------------------
# POST /rate-check  (05_Two_Pointers)
# ---------------------------------------------------------------------------
@app.post("/rate-check", tags=["Rate Limiting"])
async def rate_check(req: RateCheckRequest):
    result = check_rate_limit(req.events, req.limit, req.query_ts)
    return {
        "source": "05_Two_Pointers/ShortestSubarraywithSumofK.cpp (sliding window)",
        **result,
    }


# ---------------------------------------------------------------------------
# POST /analytics/range  (18_Advanced_Data_Structures)
# ---------------------------------------------------------------------------
@app.post("/analytics/range", tags=["Analytics"])
async def analytics_range(req: AnalyticsRequest):
    result = analytics_range_query(req.events, req.t_start, req.t_end)
    return {
        "source": "18_Advanced_Data_Structures/fallingSquares.cpp",
        **result,
    }


# ---------------------------------------------------------------------------
# POST /parse-payload  (04_Strings + 03_Arrays)
# ---------------------------------------------------------------------------
@app.post("/parse-payload", tags=["Processing"])
async def parse_payload_endpoint(req: ParsePayloadRequest):
    result = parse_payload(req.pattern, req.text)
    return {
        "source": "04_Strings/Z_Algorithm/trivial_string.cpp + 03_Arrays/Prefix_Sum",
        **result,
    }


# ---------------------------------------------------------------------------
# POST /rollback/validate  (06_Recursion + 12_Backtracking)
# ---------------------------------------------------------------------------
@app.post("/rollback/validate", tags=["Orchestration"])
async def rollback_validate(req: RollbackValidateRequest):
    result = validate_rollback_checksum(req.values, req.expected_sum)
    return {
        "source": "06_Recursion/Basic_Recursion/SumofFirstNnumbers.cpp + 12_Backtracking",
        **result,
    }


# ---------------------------------------------------------------------------
# Run
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    uvicorn.run("nexus.server:app", host="0.0.0.0", port=8000, reload=True)
