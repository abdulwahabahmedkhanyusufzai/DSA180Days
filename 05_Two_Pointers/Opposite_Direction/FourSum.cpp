#include <vector>
using namespace std;
class Solution {
public:
  vector<vector<int>> fourSum(vector<int> &nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int target = -nums[i] - nums[j];
        int left = j + 1, right = n - 1;
        while (left < right) {
          if (nums[left] + nums[right] == target) {
            ans.push_back({nums[i], nums[j], nums[left], nums[right]});
            left++;
            right--;
          } else if (nums[left] + nums[right] < target) {
            left++;
          } else {
            right--;
          }
        }
      }
    }
    return ans;
  }
};