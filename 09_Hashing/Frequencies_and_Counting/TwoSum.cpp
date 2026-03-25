class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> num_map; // Stores {number, index}

    for (int i = 0; i < nums.size(); i++) {
      int complement = target - nums[i];

      // If the complement is in our map, we found the pair
      if (num_map.find(complement) != num_map.end()) {
        return {num_map[complement], i};
      }

      // Otherwise, add the current number and its index to the map
      num_map[nums[i]] = i;
    }

    return {}; // Return empty if no solution exists
  }
};