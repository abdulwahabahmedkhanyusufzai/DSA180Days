#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<int> X(n + 2, -1);
    for (int i = 1; i <= n; ++i) {
        cin >> X[i];
    }
    
    // Check if any fixed parent is mathematically impossible (P_i >= i)
    for (int i = 1; i <= n; ++i) {
        if (X[i] != -1 && X[i] >= i) {
            cout << 0 << "\n";
            return;
        }
    }

    // Add a dummy node to seamlessly close the entire forest to the root 0
    X[n + 1] = 0;

    // Check for crossing edges
    for (int i = 1; i <= n + 1; ++i) {
        if (X[i] == -1) continue;
        for (int j = i + 1; j <= n + 1; ++j) {
            if (X[j] == -1) continue;
            // Crossing condition: u1 < u2 < v1 < v2
            if (X[i] < X[j] && X[j] < i) {
                cout << 0 << "\n";
                return;
            }
        }
    }

    vector<pair<int, int>> edges;
    for (int i = 1; i <= n + 1; ++i) {
        if (X[i] != -1) {
            edges.push_back({X[i], i});
        }
    }

    // Process from smallest (innermost) intervals to largest (outermost)
    sort(edges.begin(), edges.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return (a.second - a.first) < (b.second - b.first);
    });

    vector<int> skip_to(n + 2);
    for (int i = 0; i <= n + 1; ++i) {
        skip_to[i] = i + 1;
    }

    long long ans = 1;

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;

        vector<int> seq;
        int curr = u;
        while (curr < v) {
            seq.push_back(curr);
            curr = skip_to[curr];
        }

        int K = seq.size();
        
        // DP Array representing stack sizes
        vector<long long> dp(K + 1, 0);
        dp[1] = 1; // Root of the current subproblem

        for (int i = 1; i < K; ++i) {
            vector<long long> next_dp(K + 1, 0);
            int node = seq[i];
            
            if (X[node] != -1) { 
                // Forced Node: Attaches directly to predecessor, popping nothing 
                for (int s = 2; s <= K; ++s) {
                    next_dp[s] = dp[s - 1];
                }
            } else { 
                // Free Node: Can pop any amount but strictly bounded by subproblem root
                long long sum = 0;
                for (int s = K; s >= 2; --s) {
                    sum = (sum + dp[s - 1]) % MOD;
                    next_dp[s] = sum;
                }
            }
            dp = next_dp;
        }

        long long sum_dp = 0;
        for (int s = 1; s <= K; ++s) {
            sum_dp = (sum_dp + dp[s]) % MOD;
        }

        ans = (ans * sum_dp) % MOD;
        skip_to[u] = v; // Contract the interval for outer subproblems
    }

    cout << ans << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
