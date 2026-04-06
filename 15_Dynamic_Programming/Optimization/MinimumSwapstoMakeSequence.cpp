#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        
        // Base case for index 0
        int prev_keep = 0;
        int prev_swap = 1;
        
        for (int i = 1; i < n; i++) {
            // Initialize current states to a very large number
            int curr_keep = 1e9;
            int curr_swap = 1e9;
            
            // Condition 1: Elements are strictly increasing without any cross-swapping
            if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]) {
                curr_keep = prev_keep;
                curr_swap = prev_swap + 1;
            }
            
            // Condition 2: Elements would be strictly increasing if we cross-swap
            if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
                curr_keep = min(curr_keep, prev_swap);
                curr_swap = min(curr_swap, prev_keep + 1);
            }
            
            // Update previous states for the next iteration
            prev_keep = curr_keep;
            prev_swap = curr_swap;
        }
        
        return min(prev_keep, prev_swap);
    }
};
