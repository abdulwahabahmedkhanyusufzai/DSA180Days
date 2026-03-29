class Solution {
public:
  void solve(vector<int> &nums, int index, int target, vector<int> &current,
             vector<vector<int>> &ans) {
    if (target == 0) {
      ans.push_back(current);
      return;
    }
    if (target < 0) {
      return;
    }
    for (int i = index; i < nums.size(); i++) {
      current.push_back(nums[i]);
      solve(nums, i, target - nums[i], current, ans);
      current.pop_back();
    }
  }
  vector<vector<int>> combinationSum(vector<int> &nums, int target) {
    vector<vector<int>> ans;
    vector<int> current;
    solve(nums, 0, target, current, ans);
    return ans;
  }
};