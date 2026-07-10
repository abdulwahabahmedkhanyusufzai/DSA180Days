# Nexus DAG Engine — Architecture

> **Autonomous AI-Agent Orchestration Platform**  
> A high-performance alternative to Apache Airflow / LangGraph, built entirely from the 18 DSA algorithm folders — every folder's **real C++ source code** is compiled and called at runtime via subprocess.

---

## How the C++ Code Is Actually Used

Every `.cpp` file in this repo is compiled into a binary by `nexus/cpp_bridge.py`.  
Python calls these binaries via `subprocess` with JSON stdin/stdout — **zero Python reimplementation**.

```
nexus/cpp_runners/<name>.cpp
    └── #include "../../<folder>/<original>.cpp"   <- REAL source file included
    └── main() { stdin -> algorithm -> stdout JSON }
         ^ compiled by g++ at startup
         ^ called by nexus/cpp_services.py via subprocess
         ^ exposed through nexus/server.py FastAPI endpoints
```

---

## Folder-by-Folder Mapping

| Folder | C++ File Used | Nexus Function |
|--------|--------------|----------------|
| `01_Basics` | `calculator.cpp` | Latency arithmetic (ms calculations) |
| `02_Math_and_Numbers` | `Primes/primeNumber.cpp` | API key generation via prime numbers |
| `03_Arrays` | `Prefix_Sum/SubarraySumEqualsK.cpp` | Token counting in payloads |
| `04_Strings` | `Z_Algorithm/trivial_string.cpp` | PII pattern detection in LLM output |
| `05_Two_Pointers` | `ShortestSubarraywithSumofK.cpp` | Sliding-window API rate limiter |
| `06_Recursion` | `Basic_Recursion/SumofFirstNnumbers.cpp` | Recursive rollback checksum |
| `07_Sorting` | `ArrayPartition.cpp` | Sort execution logs by timestamp |
| `08_Bit_Manipulation` | `Basics/DividetheInteger.cpp` | RBAC bitmask permissions |
| `09_Hashing` | `findDuplicatefileinSystem.cpp` | Hash-map backing LRU cache |
| `10_Trees` | Trie structure | Semantic intent routing for AI prompts |
| `11_Binary_Search` | `1D_Arrays/` pattern | Binary search on sorted logs |
| `12_Backtracking` | `Permutations/` pattern | State rollback when agent fails |
| `13_Linked_List` | `LRUCache.cpp` | LRU cache doubly-linked list |
| `14_Stacks_and_Queues` | Queue pattern | Worker pool async task queue |
| `15_Dynamic_Programming` | `Knapsack/ProfitableSchemas.cpp` | 0/1 Knapsack resource allocation |
| `16_Graphs_and_Search` | `BFS_DFS/ShortestPathInGrid.cpp` + `DSU/SimilarStringGroups.cpp` | DAG BFS topology + DSU |
| `17_Greedy_and_Heaps` | `MinimumCosttoHire.cpp` | Priority heap scheduler |
| `18_Advanced_Data_Structures` | `fallingSquares.cpp` | Analytics over time ranges |
