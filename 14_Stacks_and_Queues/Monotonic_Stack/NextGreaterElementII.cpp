#include <stack>
#include <vector>


using namespace std;

class Solution {
public:
  vector<int> nextGreaterElements(vector<int> &nums) {
    int n = nums.size();
    vector<int> res(n, -1);
    stack<int> st;

    // Loop twice to simulate the circular array behavior
    for (int i = 0; i < 2 * n; ++i) {
      int current_idx = i % n;

      // While stack is not empty and we found a strictly greater element
      while (!st.empty() && nums[st.top()] < nums[current_idx]) {
        res[st.top()] = nums[current_idx];
        st.pop();
      }

      // We only need to push indices to the stack during the first pass
      // The second pass is just to resolve any remaining elements in the stack
      if (i < n) {
        st.push(current_idx);
      }
    }

    return res;
  }
};