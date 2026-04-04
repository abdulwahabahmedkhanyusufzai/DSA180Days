#include <algorithm>
#include <string>
#include <vector>


using namespace std;

class Solution {
private:
  // Helper function to check if string 'a' is a subsequence of string 'b'
  bool isSubsequence(const string &a, const string &b) {
    if (a.length() > b.length())
      return false;

    int i = 0; // Pointer for 'a'
    for (int j = 0; j < b.length() && i < a.length(); ++j) {
      if (a[i] == b[j]) {
        i++;
      }
    }
    return i == a.length();
  }

public:
  int findLUSlength(vector<string> &strs) {
    // Sort strings by length in descending order
    sort(strs.begin(), strs.end(), [](const string &a, const string &b) {
      return a.length() > b.length();
    });

    int n = strs.size();

    for (int i = 0; i < n; ++i) {
      bool isUncommon = true;

      for (int j = 0; j < n; ++j) {
        if (i == j)
          continue; // Don't compare the string to itself

        // If strs[i] is a subsequence of strs[j], it's not an uncommon
        // subsequence
        if (isSubsequence(strs[i], strs[j])) {
          isUncommon = false;
          break;
        }
      }

      // Because the array is sorted descending by length, the first valid
      // string is the longest
      if (isUncommon) {
        return strs[i].length();
      }
    }

    return -1;
  }
};