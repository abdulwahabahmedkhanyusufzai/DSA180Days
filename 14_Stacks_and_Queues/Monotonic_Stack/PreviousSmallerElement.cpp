class Solution {
public:
  vector<int> previousSmallerElement(vector<int> &nums) {
    vector<int> result(nums.size());
    stack<int> s;
    for (int i = 0; i < nums.size(); i++) {
      while (!s.empty() && s.top() >= nums[i]) {
        s.pop();
      }
      result[i] = s.empty() ? -1 : s.top();
      s.push(nums[i]);
    }
    return result;
  }
}