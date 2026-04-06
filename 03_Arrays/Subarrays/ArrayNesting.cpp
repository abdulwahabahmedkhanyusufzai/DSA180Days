#include <algorithm>
#include <vector>


using namespace std;

class Solution {
public:
  int arrayNesting(vector<int> &nums) {
    int max_len = 0;

    for (int i = 0; i < nums.size(); ++i) {
      // Only explore if we haven't visited this index before
      if (nums[i] != -1) {
        int curr_len = 0;
        int curr_idx = i;

        // Follow the cycle until we hit an already visited element
        while (nums[curr_idx] != -1) {
          int next_idx = nums[curr_idx]; // Remember the next jump
          nums[curr_idx] = -1;           // Mark current as visited
          curr_idx = next_idx;           // Make the jump
          curr_len++;
        }

        // Update the global maximum cycle length
        max_len = max(max_len, curr_len);
      }
    }

    return max_len;
  }
};