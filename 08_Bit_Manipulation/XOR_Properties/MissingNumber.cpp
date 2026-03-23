class Solution {
public:
  int missingNumber(vector<int> &nums) {
    int n = nums.size();
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;

    for (int num : nums) {
      actualSum += num;
    }

    return expectedSum - actualSum;
  }
};
class Solution {
public:
  int missingNumber(vector<int> &nums) {
    int n = nums.size();
    int result = n; // Start with n because the loop below only goes up to n-1

    for (int i = 0; i < n; i++) {
      result ^= i;       // XOR the index
      result ^= nums[i]; // XOR the value
    }

    return result;
  }
};