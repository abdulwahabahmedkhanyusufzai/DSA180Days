class Solution {
public:
  int largestSubmatrix(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        // Step 1: Calculate Heights
        if (matrix[i][j] == 1 && i > 0) {
          matrix[i][j] += matrix[i - 1][j];
        }
      }

      // Step 2: Create a copy of the row and sort it descending
      vector<int> currRow = matrix[i];
      sort(currRow.begin(), currRow.end(), greater<int>());

      // Step 3: Calculate max area for this row
      for (int j = 0; j < m; j++) {
        maxArea = max(maxArea, currRow[j] * (j + 1));
      }
    }
    return maxArea;
  }
};