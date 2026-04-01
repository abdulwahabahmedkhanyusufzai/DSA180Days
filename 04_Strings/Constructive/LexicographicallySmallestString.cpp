#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string generateString(string str1, string str2) {
    int n = str1.length();
    int m = str2.length();
    int L = n + m - 1;
    string word(L, '?');

    // Step 1: Apply all 'T' constraints
    for (int i = 0; i < n; ++i) {
      if (str1[i] == 'T') {
        for (int j = 0; j < m; ++j) {
          // If a character is already set by another 'T' constraint and
          // contradicts, it's impossible.
          if (word[i + j] != '?' && word[i + j] != str2[j]) {
            return "";
          }
          word[i + j] = str2[j];
        }
      }
    }

    // Step 2: Track the "last available ?" for each 'F' constraint
    // check_F[k] will store all 'F' constraint starting indices that have their
    // last '?' at index k
    vector<vector<int>> check_F(L);
    for (int i = 0; i < n; ++i) {
      if (str1[i] == 'F') {
        int last_q = -1;
        for (int j = 0; j < m; ++j) {
          if (word[i + j] == '?') {
            last_q = i + j;
          }
        }

        if (last_q == -1) {
          // Window is fully locked by 'T' constraints. Check if it violates the
          // 'F' constraint.
          bool isMatch = true;
          for (int j = 0; j < m; ++j) {
            if (word[i + j] != str2[j]) {
              isMatch = false;
              break;
            }
          }
          if (isMatch)
            return ""; // 'F' constraint failed
        } else {
          // Defer evaluating this 'F' constraint until we reach its final '?'
          check_F[last_q].push_back(i);
        }
      }
    }

    // Step 3: Greedily fill the string from left to right to ensure
    // lexicographically smallest result
    for (int k = 0; k < L; ++k) {
      if (word[k] == '?') {
        vector<bool> forbidden(26, false);

        // Check all 'F' constraints that MUST be satisfied at this specific
        // index
        for (int start_idx : check_F[k]) {
          bool isMatch = true;
          for (int j = 0; j < m; ++j) {
            if (start_idx + j == k)
              continue; // Skip the character we are currently placing
            if (word[start_idx + j] != str2[j]) {
              isMatch = false;
              break;
            }
          }
          // If all other characters match str2, we cannot use the corresponding
          // str2 character here
          if (isMatch) {
            forbidden[str2[k - start_idx] - 'a'] = true;
          }
        }

        // Pick the smallest character ('a' to 'z') that hasn't been forbidden
        char chosen = '?';
        for (int c = 0; c < 26; ++c) {
          if (!forbidden[c]) {
            chosen = 'a' + c;
            break;
          }
        }

        if (chosen == '?')
          return ""; // Cannot satisfy constraints
        word[k] = chosen;
      }
    }

    return word;
  }
};