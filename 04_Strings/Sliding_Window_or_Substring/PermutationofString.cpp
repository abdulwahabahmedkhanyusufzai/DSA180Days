#include <string>
#include <vector>
using namespace std;
class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    int n = s1.length();
    int m = s2.length();
    if (n > m) {
      return false;
    }
    vector<int> s1Count(26, 0);
    vector<int> s2Count(26, 0);
    for (int i = 0; i < n; i++) {
      s1Count[s1[i] - 'a']++;
      s2Count[s2[i] - 'a']++;
    }
    if (s1Count == s2Count) {
      return true;
    }
    for (int i = n; i < m; i++) {
      s2Count[s2[i] - 'a']++;
      s2Count[s2[i - n] - 'a']--;
      if (s1Count == s2Count) {
        return true;
      }
    }
    return false;
  }
};