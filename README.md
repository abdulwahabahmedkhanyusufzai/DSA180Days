# Nexus DAG Engine: Autonomous AI-Agent Orchestration Platform

A high-performance, stateful execution engine designed as a lightweight alternative to Apache Airflow or LangGraph. Nexus models multi-agent workflows as Directed Acyclic Graphs (DAGs) and executes them concurrently using real, compiled C++ algorithm binaries from all 18 folders of this repository.

---

## 🏗️ System Architecture

The Nexus engine handles workflow routing, task scheduling, resource allocation, caching, rate-limiting, and error-rollback through a series of specialized subsystems:

```
[ Incoming JSON Prompt ]
         │
         ▼
 10_Trees (Trie Semantic Router) ──► Maps prompt keyword to specialized agent type
         │
         ▼
 17_Greedy_and_Heaps (Priority Queue) ──► Re-orders tasks by VIP/priority weight
         │
         ▼
 15_Dynamic_Programming (Knapsack) ──► Packs tasks optimally into CPU/RAM budgets
         │
         ▼
 16_Graphs_and_Search (BFS Kahn's) ──► Traverses levels and schedules parallel tasks
         │
 ┌───────┴─────────────────────────┐
 │                                 │
 ▼                                 ▼
[ Agent A Execution ]     [ Agent B Execution ] ──► LRU Cache (13_Linked_List / 09_Hashing)
 │                                 │
 └───────┬─────────────────────────┘
         │
         ▼
 12_Backtracking (Rollback Engine) ──► Backtracks state dynamically if agent fails
```

---

## 📦 How the 18 DSA Subsystems Are Utilized

| Category | DSA Folder | Algorithm & C++ Source | Infrastructure Role |
| :--- | :--- | :--- | :--- |
| **Core Workflow** | `16_Graphs_and_Search` | BFS Kahn's (`ShortestPathInGrid.cpp`) + DSU (`SimilarStringGroups.cpp`) | Computes topological execution order and detects orphaned agents. |
| **Recovery** | `12_Backtracking` & `06_Recursion` | Depth-first search backtracking (`Permutations/`) + Recursion (`SumofFirstNnumbers.cpp`) | Traverses execution history to roll back downstream database side-effects in reverse order on agent failure. |
| **Scheduling** | `17_Greedy_and_Heaps` & `14_Stacks_and_Queues` | Min-heap ordering (`MinimumCosttoHire.cpp`) + Queue loops (`ImplementQueueusingStack.cpp`) | Manages task worker dispatch pools; prioritizes critical/VIP processes in $O(\log n)$ time. |
| **Optimization** | `15_Dynamic_Programming` | 2D 0/1 Knapsack (`ProfitableSchemas.cpp`) | Packs tasks into worker nodes to maximize value while respecting RAM/CPU budgets. |
| **Cost Reduction**| `13_Linked_List` & `09_Hashing` | Doubly-linked list + Hash map (`LRUCache.cpp`) | Returns O(1) cached LLM agent responses for identical prompt signatures. |
| **Throttling** | `05_Two_Pointers` | Sliding window (`ShortestSubarraywithSumofK.cpp`) | Monitors active TPM (tokens-per-minute) usage to prevent API rate-limits. |
| **Routing** | `10_Trees` | Trie Prefix Tree (`PrefixandSuffixSearch.cpp`) | Evaluates prompts to instantly match keywords and route workflows to specialized agents. |
| **Processing** | `04_Strings` & `03_Arrays` | Z-Algorithm (`trivial_string.cpp`) + Prefix Sum (`SubarraySumEqualsK.cpp`) | Scans payloads for PII/secrets and counts tokens in whitespace arrays. |
| **Observability** | `18_Advanced_Data_Structures` | Segment Tree / Coordinate compression (`fallingSquares.cpp`) | Computes real-time analytics summaries across time ranges in $O(\log n)$ time. |
| **Logging** | `11_Binary_Search` & `07_Sorting` | Binary Search (`1D_Arrays/`) + Quick/Merge Sort (`ArrayPartition.cpp`) | Sorts timestamped logs and identifies the exact millisecond of process crashes. |
| **Security** | `08_Bit_Manipulation` | Bitmask permissions (`Basics/DividetheInteger.cpp`) | Encodes agent privileges (READ/WRITE/EXEC/DELETE/ADMIN) into a single integer. |
| **Primitives** | `01_Basics` & `02_Math_and_Numbers` | Primes (`Primes/primeNumber.cpp`) + Math (`Basic_Operations/calculator.cpp`) | Generates secure API keys using prime number sets and runs high-precision math calculations. |

---

## 🛠️ C++ Native Process Bridge

To ensure real C++ code is used directly:
1. Python compiles the runner wrapper files inside `nexus/cpp_runners/*.cpp`.
2. These runners `#include` the actual LeetCode-style algorithm files from your repository folders.
3. The server communicates with these binaries using native standard I/O (stdin/stdout) passing structured JSON.

---

## 🚀 Quick Start Guide

### Prerequisites
* **Python 3.8+**
* **C++ Compiler (`g++`)** (e.g., MinGW-w64 on Windows or GCC on macOS/Linux)

### 1. Installation
Install the required packages:
```bash
pip install -r requirements.txt
```

### 2. Start the Server
Run the bootstrapper (which automatically builds and compiles all C++ dependencies):
```bash
python main.py
```

### 3. Open the Frontend
Launch **[`frontend/index.html`](frontend/index.html)** in any browser. It connects automatically to the FastAPI backend on `http://localhost:8000`.

---

## 📡 API Reference Summary

* `POST /execute-workflow` — Runs topological sort, greedy queue, knapsack pack, and schedules task blocks.
* `POST /route-prompt` — Selects target AI agent using the Prefix Trie.
* `POST /rbac/check` — Tests role bitmask bounds.
* `GET /keygen` — Generates cryptographically secure keys.
* `POST /cache/get` — O(1) cache retrieval.
* `POST /cache/put` — O(1) cache storage.
