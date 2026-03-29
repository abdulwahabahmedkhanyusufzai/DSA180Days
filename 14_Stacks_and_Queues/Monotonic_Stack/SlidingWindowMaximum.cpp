#include <vector>

using namespace std;

class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    vector<int> result;
    for (int i = 0; i <= nums.size() - k; i++) {
      int maxVal = nums[i];
      for (int j = i + 1; j < i + k; j++) {
        if (nums[j] > maxVal) {
          maxVal = nums[j];
        }
      }
      result.push_back(maxVal);
    }
    return result;
  }
};