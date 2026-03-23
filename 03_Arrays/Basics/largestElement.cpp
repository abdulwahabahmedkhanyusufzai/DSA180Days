class Solution {
public:
  int largestElement(vector<int> &nums) {
    int largest = INT_MIN;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
      if (nums[i] > largest) {
        largest = nums[i];
      }
    }
    return largest;
  }
};