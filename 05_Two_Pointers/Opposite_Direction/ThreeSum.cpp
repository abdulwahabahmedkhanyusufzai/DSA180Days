#include <vector>

using namespace std;
class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) {
      int j = i + 1, k = n - 1;
      while (j < k) {
        if (nums[i] + nums[j] + nums[k] == 0) {
          ans.push_back({nums[i], nums[j], nums[k]});
          j++;
          k--;
        } else if (nums[i] + nums[j] + nums[k] < 0) {
          j++;
        } else {
          k--;
        }
      }
    }
  }
  return ans;
};