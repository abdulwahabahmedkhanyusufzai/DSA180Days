class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int start = -1, end = -1;
        int max_val = nums[0];
        int min_val = nums[n - 1];

        // Find the rightmost out-of-order element
        for (int i = 1; i < n; i++) {
            if (nums[i] < max_val) {
                end = i;
            } else {
                max_val = nums[i];
            }
        }

        // Find the leftmost out-of-order element
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] > min_val) {
                start = i;
            } else {
                min_val = nums[i];
            }
        }

        // If start is still -1, the array is already sorted
        if (start == -1) return 0;

        return end - start + 1;
    }
};
