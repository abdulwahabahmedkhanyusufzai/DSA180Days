class Solution {
public:
  int findMaxConsecutiveOnes(vector<int> &nums) {
    int max_count = 0;
    int current_count = 0;

    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == 1) {
        current_count++;
        // Update max_count if current_count is larger
        max_count = max(max_count, current_count);
      } else {
        // Streak broken, reset
        current_count = 0;
      }
    }

    return max_count;
  }
};