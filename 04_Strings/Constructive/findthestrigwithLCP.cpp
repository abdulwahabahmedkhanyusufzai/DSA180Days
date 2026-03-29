#include <string>
#include <vector>


using namespace std;

class Solution {
public:
  string findTheString(vector<vector<int>> &lcp) {
    int n = lcp.size();
    string s(n, ' ');
    char curr_char = 'a';

    // 1. Greedy construction
    for (int i = 0; i < n; ++i) {
      if (s[i] != ' ')
        continue; // Already assigned
      if (curr_char > 'z')
        return ""; // More than 26 groups needed

      for (int j = i; j < n; ++j) {
        if (lcp[i][j] > 0) {
          s[j] = curr_char;
        }
      }
      curr_char++;
    }

    // 2. Comprehensive Verification
    // Check if any characters are still unassigned (shouldn't happen with valid
    // input)
    for (int i = 0; i < n; ++i) {
      if (s[i] == ' ')
        return "";
    }

    // Validate the matrix against the string using DP
    for (int i = n - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        int actual_lcp = 0;
        if (s[i] == s[j]) {
          if (i + 1 < n && j + 1 < n) {
            actual_lcp = 1 + lcp[i + 1][j + 1];
          } else {
            actual_lcp = 1;
          }
        }

        if (lcp[i][j] != actual_lcp) {
          return "";
        }
      }
    }

    return s;
  }
};