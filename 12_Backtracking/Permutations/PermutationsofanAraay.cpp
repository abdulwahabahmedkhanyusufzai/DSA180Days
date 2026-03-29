class Solution {
public:
  void generatePermutations(vector<int> &nums, int index, vector<int> &current,
                            vector<vector<int>> &ans) {
    if (index == nums.size()) {
      ans.push_back(current);
      return;
    }
    for (int i = index; i < nums.size(); i++) {
      swap(nums[index], nums[i]);
      current.push_back(nums[index]);
      generatePermutations(nums, index + 1, current, ans);
      current.pop_back();
      swap(nums[index], nums[i]);
    }
  }
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> ans;
    vector<int> current;
    generatePermutations(nums, 0, current, ans);
    return ans;
  }
};