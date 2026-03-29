#include <vector>
using namespace std;
class Solution {
public:
  vector<int> nextGreaterElement(vector<int> &nums) {
    vector<int> result(nums.size());
    stack<int> s;
    for (int i = nums.size() - 1; i >= 0; i--) {
      while (!s.empty() && s.top() <= nums[i]) {
        s.pop();
      }
      result[i] = s.empty() ? -1 : s.top();
      s.push(nums[i]);
    }
    return result;
  }
};