class Solution {
public:
  vector<int> unionArray(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size(), m = nums2.size();
    int i = 0, j = 0;
    vector<int> result;
    while (i < n && j < m) {
      if (i > 0 && nums1[i] == nums1[i - 1]) {
        i++;
        continue;
      }
      if (j > 0 && nums2[j] == nums2[j - 1]) {
        j++;
        continue;
      }
      if (nums1[i] < nums2[j]) {
        result.push_back(nums1[i]);
        i++;
      } else if (nums2[j] < nums1[i]) {
        result.push_back(nums2[j]);
        j++;
      } else {
        result.push_back(nums1[i]);
        i++;
        j++;
      }
    }
    while (i < n) {
      if (i == 0 || nums1[i] != nums1[i - 1]) {
        result.push_back(nums1[i]);
      }
      i++;
    }

    while (j < m) {
      if (j == 0 || nums2[j] != nums2[j - 1]) {
        result.push_back(nums2[j]);
      }
      j++;
    }
    return result;
  }
};
