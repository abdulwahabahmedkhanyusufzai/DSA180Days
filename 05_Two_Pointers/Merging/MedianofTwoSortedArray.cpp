#include <vector>
using namespace std;

class Solution {
public:
  double medianOfTwoSortedArray(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size();
    int m = nums2.size();
    int i = 0, j = 0;
    int median1 = -1, median2 = -1;
    for (int count = 0; count <= (n + m) / 2; count++) {
      median1 = median2;
      if (i < n && j < m) {
        if (nums1[i] < nums2[j]) {
          median2 = nums1[i++];
        } else {
          median2 = nums2[j++];
        }
      } else if (i < n) {
        median2 = nums1[i++];
      } else {
        median2 = nums2[j++];
      }
    }
    if ((n + m) % 2 == 0) {
      return (median1 + median2) / 2.0;
    } else {
      return median2;
    }
  }
};