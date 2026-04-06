#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // If start or end is blocked, no path exists
        if (grid[0][0] == -1 || grid[n - 1][n - 1] == -1) return 0;

        // DP table tracking max cherries for robot 1 at row r1 and robot 2 at row r2
        // We use -1e9 to represent unreachable states
        vector<vector<int>> dp(n, vector<int>(n, -1e9));
        dp[0][0] = grid[0][0];

        // t is the total number of steps taken (r + c = t)
        // Max steps to reach bottom right is (n - 1) + (n - 1) = 2n - 2
        for (int t = 1; t <= 2 * n - 2; t++) {
            vector<vector<int>> next_dp(n, vector<int>(n, -1e9));
            
            // Iterate through all valid rows for robot 1 and robot 2
            int min_row = max(0, t - (n - 1));
            int max_row = min(n - 1, t);
            
            for (int r1 = min_row; r1 <= max_row; r1++) {
                for (int r2 = min_row; r2 <= max_row; r2++) {
                    int c1 = t - r1;
                    int c2 = t - r2;

                    // If either robot hits a thorn, this state is invalid
                    if (grid[r1][c1] == -1 || grid[r2][c2] == -1) {
                        continue;
                    }

                    // Collect cherries (don't double count if they are on the same cell)
                    int cherries = grid[r1][c1];
                    if (r1 != r2) {
                        cherries += grid[r2][c2];
                    }

                    // Look at the 4 possible previous moves:
                    // 1. Both moved right (r1, r2)
                    // 2. Robot 1 moved down, Robot 2 moved right (r1 - 1, r2)
                    // 3. Robot 1 moved right, Robot 2 moved down (r1, r2 - 1)
                    // 4. Both moved down (r1 - 1, r2 - 1)
                    int prev_max = dp[r1][r2]; 
                    if (r1 > 0) prev_max = max(prev_max, dp[r1 - 1][r2]);
                    if (r2 > 0) prev_max = max(prev_max, dp[r1][r2 - 1]);
                    if (r1 > 0 && r2 > 0) prev_max = max(prev_max, dp[r1 - 1][r2 - 1]);

                    // If the previous state was reachable, update current state
                    if (prev_max != -1e9) {
                        next_dp[r1][r2] = prev_max + cherries;
                    }
                }
            }
            dp = next_dp;
        }

        // Return the result at bottom-right, or 0 if unreachable
        return max(0, dp[n - 1][n - 1]);
    }
};
