#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void merge(vector<int> &nums, int left, int mid, int right) {
    vector<int> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
      if (nums[i] <= nums[j]) {
        temp.push_back(nums[i]);
        i++;
      } else {
        temp.push_back(nums[j]);
        j++;
      }
    }

    while (i <= mid) {
      temp.push_back(nums[i]);
      i++;
    }

    while (j <= right) {
      temp.push_back(nums[j]);
      j++;
    }

    for (int i = left; i <= right; i++) {
      nums[i] = temp[i - left];
    }
  }
  void mergeSort(vector<int> &nums, int left, int right) { //[3,2,1,8,4,9]
    if (left >= right)                                     // 0 >= 5
      return;

    int mid = left + (right - left) / 2; // 0+5-0/2 = 5/2 = 2
    mergeSort(nums, left, mid);          // nums,0,2
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
  }
}