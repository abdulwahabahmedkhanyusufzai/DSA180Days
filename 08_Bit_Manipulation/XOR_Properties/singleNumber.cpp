class Solution {
public:
  int singleNumber(vector<int> &nums) {
    // your code goes here
    int singleNumber = 0;
    for (int num : nums) {
      singleNumber ^= num;
    }
    return singleNumber;
  }
};