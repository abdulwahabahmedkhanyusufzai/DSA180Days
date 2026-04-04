#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        // dp[diff] stores the maximum height of the shorter support
        // for a given difference 'diff' between the two supports.
        unordered_map<int, int> dp;
        dp[0] = 0;

        for (int rod : rods) {
            // We use a copy of the current DP to avoid using the same 
            // rod multiple times in a single transition.
            unordered_map<int, int> current_dp(dp);
            
            for (auto const& [diff, low] : current_dp) {
                // Case 1: Put rod on the taller support
                // New difference = diff + rod. 
                // Shorter height remains 'low'.
                dp[diff + rod] = max(dp[diff + rod], low);

                // Case 2: Put rod on the shorter support
                if (diff >= rod) {
                    // It's still the shorter support or they become equal.
                    // New difference = diff - rod.
                    // Shorter height increases by 'rod'.
                    dp[diff - rod] = max(dp[diff - rod], low + rod);
                } else {
                    // The shorter support now becomes the taller one.
                    // New difference = rod - diff.
                    // Shorter height increases by the old 'diff'.
                    dp[rod - diff] = max(dp[rod - diff], low + diff);
                }
            }
        }

        // The answer is the shorter height when the difference is 0.
        return dp[0];
    }
};
