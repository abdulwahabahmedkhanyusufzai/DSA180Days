class Solution {
public:
  bool check(vector<int> &nums) {
    int drops = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
      // We use (i + 1) % n to wrap around and compare the last element to the
      // first element
      if (nums[i] > nums[(i + 1) % n]) {
        drops++;
      }
    }

    // If there is 0 or 1 drop, it is a valid sorted and rotated array.
    // If there are 2 or more drops, it is not.
    return drops <= 1;
  }
};