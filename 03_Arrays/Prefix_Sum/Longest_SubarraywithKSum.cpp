class Solution {
public:
  int longestSubarray(vector<int> &nums, int k) {
    unordered_map<int, int> prefix_map;
    int current_sum = 0;
    int max_len = 0;

    for (int i = 0; i < nums.size(); i++) {
      current_sum += nums[i];

      // 1. If the subarray from index 0 to i sums to k
      if (current_sum == k) {
        max_len = i + 1;
      }

      // 2. Check if we've seen a prefix sum that would leave us with k
      if (prefix_map.find(current_sum - k) != prefix_map.end()) {
        int previous_index = prefix_map[current_sum - k];
        max_len = max(max_len, i - previous_index);
      }

      // 3. Only store the FIRST time we see a sum to ensure we get the LONGEST
      // length
      if (prefix_map.find(current_sum) == prefix_map.end()) {
        prefix_map[current_sum] = i;
      }
    }

    return max_len;
  }
};