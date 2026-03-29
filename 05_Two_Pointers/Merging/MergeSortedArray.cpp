class Solution {
public:
  void mergeSortedArray(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size();
    int m = nums2.size();

    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
      if (nums1[i] < nums2[j]) {
        nums1[k++] = nums1[i++];
      } else {
        nums1[k++] = nums2[j++];
      }
    }
    while (i < n) {
      nums1[k++] = nums1[i++];
    }
    while (j < m) {
      nums1[k++] = nums2[j++];
    }
  }
};