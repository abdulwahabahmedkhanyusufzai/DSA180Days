#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k - 1);
    }

private:
    int atMostK(vector<int>& nums, int k) {
        if (k == 0) return 0;
        
        unordered_map<int, int> count;
        int left = 0, res = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            // Add the current number to the window
            if (count[nums[right]] == 0) {
                k--;
            }
            count[nums[right]]++;
            
            // If we have more than k distinct elements, shrink from the left
            while (k < 0) {
                count[nums[left]]--;
                if (count[nums[left]] == 0) {
                    k++;
                }
                left++;
            }
            
            // The number of subarrays ending at 'right' with at most k distinct 
            // elements is exactly the length of the current window.
            res += (right - left + 1);
        }
        
        return res;
    }
};
