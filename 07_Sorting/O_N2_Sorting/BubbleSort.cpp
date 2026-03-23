#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> bubbleSort(vector<int> &nums) {
    int n = nums.size();
    bool swapped;

    // Outer loop keeps track of how many passes we've made
    for (int i = 0; i < n - 1; i++) {
      swapped = false;

      // Inner loop compares adjacent elements.
      // We subtract 'i' because the largest 'i' elements are already sorted at
      // the end.
      for (int j = 0; j < n - i - 1; j++) {

        // If the current element is bigger than the next one, swap them
        if (nums[j] > nums[j + 1]) {
          swap(nums[j], nums[j + 1]);
          swapped = true;
        }
      }

      // If we went through the whole inner loop without making a single swap,
      // the array is completely sorted. We can stop early.
      if (!swapped) {
        break;
      }
    }

    return nums;
  }
};