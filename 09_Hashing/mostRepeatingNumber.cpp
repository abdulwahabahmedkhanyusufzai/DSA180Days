#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int mostFrequentElement(vector<int> &nums) {
    unordered_map<int, int> Freqmap;

    for (int num : nums) {
      Freqmap[num]++;
    }

    int maxFreq = 0;
    int result = nums[0];

    for (auto &p : Freqmap) {
      if (p.second > maxFreq) {
        maxFreq = p.second;
        result = p.first;
      }
    }
    return result
  }
};