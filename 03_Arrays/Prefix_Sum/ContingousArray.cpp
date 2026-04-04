#include <algorithm>
#include <unordered_map>
#include <vector>


using namespace std;

class Solution {
public:
  int findMaxLength(vector<int> &nums) {
    // Map stores {running_sum: first_index_seen}
    unordered_map<int, int> sum_map;

    // Base case: a sum of 0 exists at index -1 before we process any elements
    sum_map[0] = -1;

    int max_len = 0;
    int sum = 0;

    for (int i = 0; i < nums.size(); ++i) {
      // Treat 0 as -1 to use the prefix sum logic
      sum += (nums[i] == 0) ? -1 : 1;

      // If we have seen this sum before, we found a balanced subarray
      if (sum_map.find(sum) != sum_map.end()) {
        max_len = max(max_len, i - sum_map[sum]);
      } else {
        // Only record the FIRST time we see a sum to maximize the subarray
        // length
        sum_map[sum] = i;
      }
    }

    return max_len;
  }
};