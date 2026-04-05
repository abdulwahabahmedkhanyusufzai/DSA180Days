#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        
        // 1. Check if it's even possible to merge into 1 pile
        if ((n - 1) % (K - 1) != 0) return -1;

        // 2. Precompute prefix sums for O(1) range sum queries
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + stones[i];
        }

        // 3. dp[i][j] is the min cost to merge stones[i...j]
        // Initialize with a large value
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = K; len <= n; len++) { // length of the interval
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = 1e9; // Infinity

                // Try splitting the interval into two parts
                // The first part [i, m] must be mergeable into 1 pile, 
                // so m increases by (K-1)
                for (int m = i; m < j; m += K - 1) {
                    dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j]);
                }

                // If this interval can be merged into a single pile
                if ((len - 1) % (K - 1) == 0) {
                    dp[i][j] += prefixSum[j + 1] - prefixSum[i];
                }
            }
        }

        return dp[0][n - 1];
    }
};
