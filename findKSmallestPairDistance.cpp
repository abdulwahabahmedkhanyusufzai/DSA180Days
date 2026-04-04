#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        // Sort to use sliding window and binary search
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        // Minimum and maximum possible pair distances
        int low = 0;
        int high = nums[n - 1] - nums[0];
        
        // Binary search for the k-th smallest distance
        while (low < high) {
            int mid = low + (high - low) / 2;
            
            // Count how many pairs have a distance <= mid
            int count = 0;
            int left = 0;
            for (int right = 0; right < n; right++) {
                // Shrink the window if the distance exceeds mid
                while (nums[right] - nums[left] > mid) {
                    left++;
                }
                // All pairs from left to right-1 paired with 'right' are valid
                count += (right - left);
            }
            
            // If count is enough, the answer might be mid or smaller
            if (count >= k) {
                high = mid;
            } else {
                // Otherwise, the distance needs to be strictly larger
                low = mid + 1;
            }
        }
        
        return low;
    }
};
