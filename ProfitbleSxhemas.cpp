#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int mod = 1e9 + 7;
        
        // dp[i][j] = number of schemes with i members and at least j profit
        // Size is (n + 1) x (minProfit + 1)
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
        
        // Base case: 0 members and 0 profit is 1 valid scheme (doing nothing)
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }
        
        for (int k = 0; k < group.size(); k++) {
            int membersNeeded = group[k];
            int p = profit[k];
            
            // Iterate backwards to use the 1D/2D space optimization trick
            for (int i = n; i >= membersNeeded; i--) {
                for (int j = minProfit; j >= 0; j--) {
                    // New profit is at least j. 
                    // We take max(0, j - p) because any profit > minProfit 
                    // is capped at minProfit in our DP table.
                    int prevProfit = max(0, j - p);
                    dp[i][j] = (dp[i][j] + dp[i - membersNeeded][prevProfit]) % mod;
                }
            }
        }
        
        return dp[n][minProfit];
    }
};
