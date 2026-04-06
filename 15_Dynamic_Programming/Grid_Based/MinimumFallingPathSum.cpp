#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 1) return grid[0][0];

        // We only need to track the two minimums of the previous row
        int prevMin1 = 0, prevMin2 = 0, prevIdx1 = -1;

        for (int r = 0; r < n; r++) {
            int currMin1 = INT_MAX, currMin2 = INT_MAX, currIdx1 = -1;

            for (int c = 0; c < n; c++) {
                // If current column matches the index of the previous row's absolute min,
                // we must use the second minimum.
                int prevVal = (c == prevIdx1) ? prevMin2 : prevMin1;
                int sum = grid[r][c] + prevVal;

                // Update the two smallest values for the current row
                if (sum < currMin1) {
                    currMin2 = currMin1;
                    currMin1 = sum;
                    currIdx1 = c;
                } else if (sum < currMin2) {
                    currMin2 = sum;
                }
            }

            prevMin1 = currMin1;
            prevMin2 = currMin2;
            prevIdx1 = currIdx1;
        }

        return prevMin1;
    }
};
