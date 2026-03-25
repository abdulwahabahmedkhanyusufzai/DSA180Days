class Solution {
public:
  int numberOfSubmatrices(vector<vector<char>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    // 2D prefix sum arrays for 'X' and 'Y'
    // Using n+1 to handle boundaries easily
    vector<vector<int>> prefX(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> prefY(n + 1, vector<int>(m + 1, 0));

    int count = 0;

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        // Determine if current cell matches target
        int isX = (grid[i - 1][j - 1] == 'X') ? 1 : 0;
        int isY = (grid[i - 1][j - 1] == 'Y') ? 1 : 0;

        // Calculate prefix sum for 'X'
        prefX[i][j] =
            isX + prefX[i - 1][j] + prefX[i][j - 1] - prefX[i - 1][j - 1];

        // Calculate prefix sum for 'Y'
        prefY[i][j] =
            isY + prefY[i - 1][j] + prefY[i][j - 1] - prefY[i - 1][j - 1];

        // Check both constraints
        if (prefX[i][j] == prefY[i][j] && prefX[i][j] > 0) {
          count++;
        }
      }
    }

    return count;
  }
};