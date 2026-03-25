#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
 
using namespace std;
 
const int MAXN = 300005;
 
long long a[MAXN];
vector<int> adj[MAXN];
 
int parent_1[MAXN];
int in_dist[MAXN], in_leaf[MAXN];
int best_child[MAXN];
 
struct LeafOpt {
    int dist;
    int leaf;
    bool operator<(const LeafOpt& o) const {
        if (dist != o.dist) return dist < o.dist;
        return leaf > o.leaf; // Smaller index is preferred
    }
};
 
LeafOpt max_opt(LeafOpt a, LeafOpt b) {
    return (a < b) ? b : a;
}
 
LeafOpt best_child_opt[MAXN];
LeafOpt second_child_opt[MAXN];
int out_dist[MAXN], out_leaf[MAXN];
long long leaf_sum[MAXN];
int order[MAXN];
int q[MAXN];
 
// Data structure to dynamically maintain the sum of top (k-1) elements
struct TopKSum {
    int K;
    long long current_sum;
    multiset<long long> top;
    multiset<long long> bottom;
 
    void init(int k) {
        K = k;
        current_sum = 0;
        top.clear();
        bottom.clear();
    }
 
    void add(long long val) {
        if (K <= 0 || val == 0) return;
        bottom.insert(val);
        balance();
    }
 
    void remove(long long val) {
        if (K <= 0 || val == 0) return;
        auto it = bottom.find(val);
        if (it != bottom.end()) {
            bottom.erase(it);
        } else {
            it = top.find(val);
            if (it != top.end()) {
                top.erase(it);
                current_sum -= val;
            }
        }
        balance();
    }
 
    void balance() {
        if (K <= 0) return;
        while ((int)top.size() < K && !bottom.empty()) {
            auto it = prev(bottom.end());
            current_sum += *it;
            top.insert(*it);
            bottom.erase(it);
        }
        while ((int)top.size() > K) {
            auto it = top.begin();
            current_sum -= *it;
            bottom.insert(*it);
            top.erase(it);
        }
        while (!bottom.empty() && !top.empty()) {
            auto it_b = prev(bottom.end());
            auto it_t = top.begin();
            if (*it_b > *it_t) {
                long long val_b = *it_b;
                long long val_t = *it_t;
                current_sum += val_b - val_t;
                top.erase(it_t);
                bottom.erase(it_b);
                top.insert(val_b);
                bottom.insert(val_t);
            } else {
                break;
            }
        }
    }
 
    long long get_sum() {
        return current_sum;
    }
};
 
TopKSum topk;
long long max_total = 0;
 
// Get the destination leaf of node x, given its current parent px
int get_dest(int x, int px) {
    if (px == parent_1[x]) return in_leaf[x];
    else return out_leaf[px];
}
 
void build_order(int n) {
    int head = 0, tail = 0;
    q[tail++] = 1;
    parent_1[1] = 0;
    
    while (head < tail) {
        int u = q[head++];
        order[head - 1] = u;
        for (int v : adj[u]) {
            if (v == parent_1[u]) continue;
            parent_1[v] = u;
            q[tail++] = v;
        }
    }
}
 
void dfs_reroot(int u, int p) {
    long long current_total = a[u] + topk.get_sum();
    if (current_total > max_total) {
        max_total = current_total;
    }
    
    for (int v : adj[u]) {
        if (v == p) continue;
        
        // --- Move Root from u to v ---
        int dest_v = get_dest(v, u);
        topk.remove(leaf_sum[dest_v]);
        leaf_sum[dest_v] -= a[v];
        topk.add(leaf_sum[dest_v]);
        
        int dest_u = get_dest(u, v);
        topk.remove(leaf_sum[dest_u]);
        leaf_sum[dest_u] += a[u];
        topk.add(leaf_sum[dest_u]);
        
        // Explore branch
        dfs_reroot(v, u);
        
        // --- Backtrack Root from v to u ---
        topk.remove(leaf_sum[dest_u]);
        leaf_sum[dest_u] -= a[u];
        topk.add(leaf_sum[dest_u]);
        
        topk.remove(leaf_sum[dest_v]);
        leaf_sum[dest_v] += a[v];
        topk.add(leaf_sum[dest_v]);
    }
}
 
void solve() {
    int n, k;
    if (!(cin >> n >> k)) return;
 
    // Reset Memory per test case
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        adj[i].clear();
        parent_1[i] = 0;
        in_dist[i] = 0; in_leaf[i] = 0;
        best_child[i] = 0;
        best_child_opt[i] = {-1, -1};
        second_child_opt[i] = {-1, -1};
        out_dist[i] = 0; out_leaf[i] = 0;
        leaf_sum[i] = 0;
    }
 
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    if (n == 1) {
        cout << a[1] << "\n";
        return;
    }
 
    // 1. BFS to get Top-Down iteration order
    build_order(n);
 
    // 2. Bottom-Up DP (Find max inward paths)
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        bool is_leaf = true;
        LeafOpt best1 = {-1, -1};
        LeafOpt best2 = {-1, -1};
        
        for (int v : adj[u]) {
            if (v == parent_1[u]) continue;
            is_leaf = false;
            LeafOpt opt = {in_dist[v] + 1, in_leaf[v]};
            if (best1 < opt) {
                best2 = best1;
                best1 = opt;
                best_child[u] = v;
            } else if (best2 < opt) {
                best2 = opt;
            }
        }
        if (is_leaf) {
            in_dist[u] = 0;
            in_leaf[u] = u;
        } else {
            in_dist[u] = best1.dist;
            in_leaf[u] = best1.leaf;
            best_child_opt[u] = best1;
            second_child_opt[u] = best2;
        }
    }
 
    // 3. Top-Down DP (Find max outward paths)
    out_dist[1] = -1;
    out_leaf[1] = 0;
    for (int i = 0; i < n; i++) {
        int u = order[i];
        for (int v : adj[u]) {
            if (v == parent_1[u]) continue;
            
            LeafOpt alt = {-1, -1};
            if (parent_1[u] != 0) { 
                alt = max_opt(alt, {out_dist[u], out_leaf[u]});
            }
            
            if (best_child[u] == v) {
                if (second_child_opt[u].dist != -1) alt = max_opt(alt, second_child_opt[u]);
            } else {
                if (best_child_opt[u].dist != -1) alt = max_opt(alt, best_child_opt[u]);
            }
            
            if (alt.dist == -1) alt = {0, u};
            
            out_dist[v] = alt.dist + 1;
            out_leaf[v] = alt.leaf;
        }
    }
 
    // 4. Calculate initial leaf sums assuming Root is node 1
    for (int i = 2; i <= n; i++) {
        int dest = get_dest(i, parent_1[i]);
        leaf_sum[dest] += a[i];
    }
 
    // 5. Build dynamic tracking set for top K-1 leaves
    topk.init(k - 1);
    for (int i = 1; i <= n; i++) {
        if (leaf_sum[i] > 0) topk.add(leaf_sum[i]);
    }
 
    // 6. Reroot the tree dynamically to test all N possible roots in O(N log N)
    max_total = 0;
    dfs_reroot(1, 0);
 
    cout << max_total << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}
