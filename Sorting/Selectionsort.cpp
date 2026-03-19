#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> selectionSort(vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i <= n - 2; i++) {
      int min = i;
      for (int j = 0; j <= n - 1; j++) {
        if (nums[j] < nums[min]) {
          min = j;
        }
        int temp = nums[min];
        nums[min] = nums[i];
        nums[i] = temp;
      }
      return nums
    }
  }
};
