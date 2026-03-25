class Solution {
public:
  bool findRotation(vector<vector<int>> &mat, vector<vector<int>> &target) {
    int n = mat.size();

    bool c[4] = {true, true, true, true};

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (mat[i][j] != target[i][j])
          c[0] = false;

        if (mat[n - 1 - j][i] != target[i][j])
          c[1] = false;

        if (mat[n - 1 - i][n - 1 - j] != target[i][j])
          c[2] = false;

        if (mat[j][n - 1 - i] != target[i][j])
          c[3] = false;
      }
    }
    return c[0] || c[1] || c[2] || c[3];
  }
};