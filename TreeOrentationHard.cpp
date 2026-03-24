#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Standard Disjoint Set Union to check for undirected cycles
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for(int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

void solve() {
    int N;
    if (!(cin >> N)) return;
    
    vector<string> R(N);
    vector<int> out(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> R[i];
        for (int j = 0; j < N; ++j) {
            if (R[i][j] == '1') out[i]++;
        }
    }

    // $O(N)$ Bucket Sort arrays
    vector<int> bucket_head(N + 1, -1);
    vector<int> bucket_next(N, -1);
    
    vector<pair<int, int>> edges;
    vector<int> nodes;
    nodes.reserve(N);
    
    vector<int> covered(N, 0);
    int visit_id = 0;

    // 1. Find Candidate Edges
    for (int u = 0; u < N; ++u) {
        int max_out = -1;
        // Place reachable nodes into buckets based on out-degree
        for (int v = 0; v < N; ++v) {
            if (u != v && R[u][v] == '1') {
                int o = out[v];
                bucket_next[v] = bucket_head[o];
                bucket_head[o] = v;
                if (o > max_out) max_out = o;
            }
        }

        // Extract from buckets to get them in perfectly descending order
        nodes.clear();
        for (int o = max_out; o >= 0; --o) {
            int curr = bucket_head[o];
            while (curr != -1) {
                nodes.push_back(curr);
                int nxt = bucket_next[curr];
                curr = nxt;
            }
            bucket_head[o] = -1; // Reset bucket for future use
        }

        visit_id++;
        for (int v : nodes) {
            if (covered[v] != visit_id) {
                edges.push_back({u, v});
                
                // Early exit if the matrix produces too many edges (Adversarial input)
                if (edges.size() > N - 1) {
                    cout << "No\n";
                    return;
                }
                
                // Mark all descendants of v as covered so we don't process them for u
                for (int w = 0; w < N; ++w) {
                    if (R[v][w] == '1') covered[w] = visit_id;
                }
            }
        }
    }

    // 2. Verification Step 1: Exactly N-1 Edges
    if (edges.size() != N - 1) {
        cout << "No\n";
        return;
    }

    // 3. Verification Step 2: Ensure it forms an undirected tree
    DSU dsu(N);
    vector<vector<int>> adj(N);
    for (auto& edge : edges) {
        if (!dsu.unite(edge.first, edge.second)) {
            cout << "No\n";
            return;
        }
        adj[edge.first].push_back(edge.second);
    }

    // 4. Verification Step 3: Fast BFS to verify exact reachability map
    vector<int> visited(N, 0);
    int bfs_visit_id = 0;
    vector<int> q;
    q.reserve(N);

    for (int u = 0; u < N; ++u) {
        bfs_visit_id++;
        q.clear();
        q.push_back(u);
        visited[u] = bfs_visit_id;

        int head = 0;
        int reach_count = 0;
        
        while (head < q.size()) {
            int curr = q[head++];
            reach_count++;
            
            // If our generated tree reaches a node it shouldn't mathematically reach
            if (R[u][curr] != '1') {
                cout << "No\n";
                return;
            }
            
            for (int nxt : adj[curr]) {
                if (visited[nxt] != bfs_visit_id) {
                    visited[nxt] = bfs_visit_id;
                    q.push_back(nxt);
                }
            }
        }
        
        // If our generated tree missed nodes it was supposed to reach
        if (reach_count != out[u]) {
            cout << "No\n";
            return;
        }
    }

    // Completely verified
    cout << "Yes\n";
    for (auto& edge : edges) {
        cout << edge.first + 1 << " " << edge.second + 1 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}
