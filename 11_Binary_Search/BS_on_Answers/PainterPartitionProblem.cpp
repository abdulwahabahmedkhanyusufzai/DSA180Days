#include <vector>
using namespace std;

class Solution {
public:
  int painterPartitionProblem(vector<int> &nums, int n, int k) {
    int low = *max_element(nums.begin(), nums.end());
    int high = accumulate(nums.begin(), nums.end(), 0);
    int ans = -1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (isPossible(nums, mid)) {
        ans = mid;
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    return ans;
  }
  bool isPossible(vector<int> &nums, int mid) {
    int painters = 1;
    int currentSum = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (currentSum + nums[i] <= mid) {
        currentSum += nums[i];
      } else {
        painters++;
        currentSum = nums[i];
      }
    }
    return painters <= k;
  }
};