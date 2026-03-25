#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Allocate globally to avoid memory allocation overhead during queries
const int MAXN = 1000005;
int Z[MAXN];
int max_r[MAXN + 2];

void solve() {
    int n, q;
    if (!(cin >> n >> q)) return;
    string s;
    cin >> s;
    
    for (int q_idx = 0; q_idx < q; q_idx++) {
        int l, r;
        cin >> l >> r;
        
        // Convert to 0-based indexing
        l--; 
        r--; 
        
        int m = r - l + 1;
        
        // 1. Z-Algorithm mapped to the specific substring s[l...r]
        int L = 0, R = 0;
        Z[0] = m;
        for (int i = 1; i < m; i++) {
            if (i <= R) {
                Z[i] = min(R - i + 1, Z[i - L]);
            } else {
                Z[i] = 0;
            }
            
            while (i + Z[i] < m && s[l + Z[i]] == s[l + i + Z[i]]) {
                Z[i]++;
            }
            
            if (i + Z[i] - 1 > R) {
                L = i;
                R = i + Z[i] - 1;
            }
        }
        
        // 2. O(m) Sweep-Line DP
        // Reset only the memory we will use for this query
        for (int i = 0; i <= m + 1; i++) {
            max_r[i] = 0;
        }
        
        int best_v = 1;
        max_r[1] = m; // From 0, we can always jump the full length in 1 step
        
        long long total_sum = 0;
        
        for (int x = 1; x <= m; x++) {
            // Can we achieve one more piece than our current best?
            if (max_r[best_v + 1] >= x) {
                best_v++;
            }
            
            // If the current number of pieces can no longer reach x, safely drop down
            // The lazy propagation ensures mathematically correct fallback ranges
            while (best_v > 0 && max_r[best_v] < x) {
                max_r[best_v - 1] = max(max_r[best_v - 1], max_r[best_v]);
                best_v--;
            }
            
            int dp_x = best_v;
            total_sum += dp_x;
            
            // Register the reach of the newly formed piece
            if (x < m && Z[x] > 0) {
                max_r[dp_x + 1] = max(max_r[dp_x + 1], x + Z[x]);
            }
        }
        
        cout << total_sum << "\n";
    }
}

int main() {
    // Fast I/O is crucial for string problems with large outputs
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
