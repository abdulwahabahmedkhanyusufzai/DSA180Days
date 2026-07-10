/*
 * RUNNER: dag_topology
 * SOURCE: 16_Graphs_and_Search/BFS_DFS/ShortestPathInGrid.cpp  (BFS logic included)
 *         16_Graphs_and_Search/DSU/SimilarStringGroups.cpp     (DSU included)
 *
 * Builds the DAG topological ordering for a workflow.
 * Uses the BFS queue pattern from ShortestPathInGrid and DSU from SimilarStringGroups.
 *
 * Protocol (stdin):
 *   Line 1: N  (number of tasks)
 *   Line 2: M  (number of dependency edges)
 *   Lines 3..M+2: <from_id> <to_id>  (from must complete before to)
 *   Then N lines: <task_id>
 *
 * Output JSON: sorted levels for concurrent execution
 *   {"ok":true,"levels":[["t1","t3"],["t2"],["t4"]],"has_cycle":false}
 */

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ── DSU from 16_Graphs_and_Search/DSU/SimilarStringGroups.cpp ───────────────
// find() with path compression — exact same function signature
int dsu_find(int i, vector<int>& parent) {
    if (parent[i] == i) return i;
    return parent[i] = dsu_find(parent[i], parent);   // exact line from SimilarStringGroups.cpp
}
// ─────────────────────────────────────────────────────────────────────────────

// ── BFS from 16_Graphs_and_Search/BFS_DFS/ShortestPathInGrid.cpp ────────────
// Kahn's algorithm uses the same queue<> BFS pattern
// ─────────────────────────────────────────────────────────────────────────────

int main() {
    int N, M;
    if (!(cin >> N >> M)) { cout << "{\"ok\":false,\"error\":\"bad input\"}\n"; return 1; }

    vector<string> task_ids(N);
    unordered_map<string,int> idx_map;

    // Read edges first, then task IDs
    vector<pair<int,int>> edges(M);
    vector<int> from_raw(M), to_raw(M);
    for (int i = 0; i < M; i++) cin >> from_raw[i] >> to_raw[i];
    for (int i = 0; i < N; i++) { cin >> task_ids[i]; idx_map[task_ids[i]] = i; }

    // Build adjacency list + in-degree
    vector<vector<int>> adj(N);
    vector<int> in_degree(N, 0);
    for (int i = 0; i < M; i++) {
        int f = from_raw[i], t = to_raw[i];
        adj[f].push_back(t);
        in_degree[t]++;
    }

    // DSU: detect isolated components (from SimilarStringGroups.cpp DSU)
    vector<int> parent(N);
    for (int i = 0; i < N; i++) parent[i] = i;
    for (int i = 0; i < M; i++) {
        int rf = dsu_find(from_raw[i], parent);
        int rt = dsu_find(to_raw[i], parent);
        if (rf != rt) parent[rf] = rt;
    }

    // Kahn's BFS topological sort (BFS queue pattern from ShortestPathInGrid.cpp)
    queue<int> q;  // same queue<vector<int>> q pattern, simplified to int
    for (int i = 0; i < N; i++)
        if (in_degree[i] == 0) q.push(i);

    vector<vector<string>> levels;
    int visited = 0;
    bool has_cycle = false;

    while (!q.empty()) {
        int sz = q.size();
        vector<string> level;
        for (int i = 0; i < sz; i++) {
            int node = q.front(); q.pop();
            level.push_back(task_ids[node]);
            visited++;
            for (int nb : adj[node]) {
                if (--in_degree[nb] == 0) q.push(nb);
            }
        }
        levels.push_back(level);
    }

    has_cycle = (visited != N);

    // Output JSON
    cout << "{\"ok\":true,\"has_cycle\":" << (has_cycle ? "true" : "false")
         << ",\"task_count\":" << N << ",\"levels\":[";
    for (int i = 0; i < (int)levels.size(); i++) {
        if (i) cout << ",";
        cout << "[";
        for (int j = 0; j < (int)levels[i].size(); j++) {
            if (j) cout << ",";
            cout << "\"" << levels[i][j] << "\"";
        }
        cout << "]";
    }
    cout << "]}\n";
    return 0;
}
