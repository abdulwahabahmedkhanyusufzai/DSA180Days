#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> constructProductMatrix(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    const int MOD = 12345;

    // Initialize the result matrix p with the same size as grid
    vector<vector<int>> p(n, vector<int>(m));

    long long running_product = 1;

    // Pass 1: Prefix Product (Top-Left to Bottom-Right)
    // Store the product of all elements BEFORE the current cell
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        p[i][j] = running_product;
        // Update running product with the current grid value
        running_product = (running_product * (grid[i][j] % MOD)) % MOD;
      }
    }

    running_product = 1; // Reset for the second pass

    // Pass 2: Suffix Product (Bottom-Right to Top-Left)
    // Multiply the current prefix by the product of all elements AFTER the
    // current cell
    for (int i = n - 1; i >= 0; --i) {
      for (int j = m - 1; j >= 0; --j) {
        p[i][j] = (p[i][j] * running_product) % MOD;
        // Update running product with the current grid value
        running_product = (running_product * (grid[i][j] % MOD)) % MOD;
      }
    }

    return p;
  }
};