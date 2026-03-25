#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Disjoint Set Union (DSU) to check for cycles in our generated tree
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
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
    int n;
    if (!(cin >> n)) return;
    
    vector<string> R(n);
    vector<int> out(n, 0);
    
    for (int i = 0; i < n; ++i) {
        cin >> R[i];
        for (int j = 0; j < n; ++j) {
            if (R[i][j] == '1') out[i]++;
        }
    }

    vector<pair<int, int>> edges;
    
    // 1. Identify direct children for each node
    for (int u = 0; u < n; ++u) {
        vector<int> reachable;
        for (int v = 0; v < n; ++v) {
            if (u != v && R[u][v] == '1') {
                reachable.push_back(v);
            }
        }
        
        // Sort reachable nodes by out-degree descending
        sort(reachable.begin(), reachable.end(), [&](int a, int b) {
            return out[a] > out[b];
        });

        vector<bool> covered(n, false);
        for (int v : reachable) {
            if (!covered[v]) {
                edges.push_back({u, v});
                
                // Early exit: A valid tree can only have exactly N-1 edges
                if (edges.size() > n - 1) { 
                    cout << "No\n";
                    return;
                }
                
                // Mark everything reachable from v as covered for u
                for (int w = 0; w < n; ++w) {
                    if (R[v][w] == '1') covered[w] = true;
                }
            }
        }
    }

    // 2. Verify we have exactly N - 1 edges
    if (edges.size() != n - 1) {
        cout << "No\n";
        return;
    }

    // 3. Verify it forms an acyclic undirected tree using DSU
    DSU dsu(n);
    vector<vector<int>> adj(n);
    for (auto& edge : edges) {
        if (!dsu.unite(edge.first, edge.second)) {
            cout << "No\n"; // Cycle detected
            return;
        }
        adj[edge.first].push_back(edge.second);
    }

    // 4. Verify exact reachability matches the input matrix R
    for (int u = 0; u < n; ++u) {
        vector<bool> vis(n, false);
        vector<int> q;
        q.push_back(u);
        vis[u] = true;
        
        int head = 0;
        int reach_count = 0;

        while (head < q.size()) {
            int curr = q[head++];
            reach_count++;
            
            // Generated tree reached a node it shouldn't have
            if (R[u][curr] != '1') {
                cout << "No\n";
                return;
            }
            
            for (int nxt : adj[curr]) {
                if (!vis[nxt]) {
                    vis[nxt] = true;
                    q.push_back(nxt);
                }
            }
        }

        // Generated tree missed nodes it was supposed to reach
        if (reach_count != out[u]) {
            cout << "No\n";
            return;
        }
    }

    // If all checks pass, we found a valid orientation!
    cout << "Yes\n";
    for (auto& edge : edges) {
        cout << edge.first + 1 << " " << edge.second + 1 << "\n";
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}
