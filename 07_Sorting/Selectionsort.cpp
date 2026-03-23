#include <iostream>
#include <vector>

using namespace std;

class Solution {
public: //[2,5,6,2,1,8]
        //[1,5,6,2,2,8]
  vector<int> selectionSort(vector<int> &nums) {
    int n = nums.size();                     // n = 6
    for (int i = 0; i <= n - 2; i++) {       // i=0 to 4
      int min = i;                           // 1
      for (int j = i + 1; j <= n - 1; j++) { // j=0 to 5
        if (nums[j] < nums[min]) {           // 1 < 2
          min = j;                           // 4
        }
      }
      int temp = nums[min]; // 1
      nums[min] = nums[i];  // 2
      nums[i] = temp;       // 1
    }
    return nums;
  }
};
