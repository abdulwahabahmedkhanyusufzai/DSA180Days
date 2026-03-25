#include <numeric>
#include <vector>


using namespace std;

class Solution {
public:
  bool canPartitionGrid(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    long long totalSum = 0;
    for (const auto &row : grid) {
      for (int val : row)
        totalSum += val;
    }

    // If total sum is odd, we can't partition into two equal integers
    if (totalSum % 2 != 0)
      return false;
    long long target = totalSum / 2;

    // 1. Try Horizontal Cuts (between row i and i+1)
    long long rowPrefix = 0;
    for (int i = 0; i < m - 1;
         ++i) { // m-1 to ensure both sections are non-empty
      for (int j = 0; j < n; ++j) {
        rowPrefix += grid[i][j];
      }
      if (rowPrefix == target)
        return true;
    }

    // 2. Try Vertical Cuts (between column j and j+1)
    long long colPrefix = 0;
    for (int j = 0; j < n - 1;
         ++j) { // n-1 to ensure both sections are non-empty
      for (int i = 0; i < m; ++i) {
        colPrefix += grid[i][j];
      }
      if (colPrefix == target)
        return true;
    }

    return false;
  }
};