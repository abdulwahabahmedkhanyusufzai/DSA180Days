class Solution {
public:
  int secondLargestElement(vector<int> &nums) {
    // your code goes here
    int largest = INT_MIN;
    int secondLargest = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
      if (nums[i] > largest) {   //[8, 8, 7, 6, 5]
        secondLargest = largest; // INT_MIN
        largest = nums[i];       // 8

      } else if (nums[i] > secondLargest && nums[i] < largest) {
        secondLargest = nums[i];
      }
    }
    return secondLargest == INT_MIN ? -1 : secondLargest;
  }
};