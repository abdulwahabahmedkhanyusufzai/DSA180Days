class Solution {
public:
  void recursiveBubbleSort(vector<int> &nums, int n) {
    if (n == 1)
      return;

    for (int i = 0; i < n - 1; i++) {
      if (nums[i] > nums[i + 1]) {
        swap(nums[i], nums[i + 1]);
      }
    }
    recursiveBubbleSort(nums, n - 1);
  }
}