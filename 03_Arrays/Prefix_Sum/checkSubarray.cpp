#include <unordered_map>
#include <vector>


using namespace std;

class Solution {
public:
  bool checkSubarraySum(vector<int> &nums, int k) {
    // Map to store the first time we see a particular remainder: {remainder:
    // index}
    unordered_map<int, int> mod_map;

    // Initialize for subarrays starting from index 0 that are multiples of k
    mod_map[0] = -1;

    int prefix_sum = 0;

    for (int i = 0; i < nums.size(); ++i) {
      prefix_sum += nums[i];

      // Calculate the remainder of the current prefix sum
      int remainder = prefix_sum % k;

      // If we have seen this remainder before
      if (mod_map.find(remainder) != mod_map.end()) {
        // Check if the subarray length is at least 2
        if (i - mod_map[remainder] > 1) {
          return true;
        }
      } else {
        // Only store the index the FIRST time we see the remainder.
        // We want to maximize the distance between matching remainders.
        mod_map[remainder] = i;
      }
    }

    return false;
  }
};