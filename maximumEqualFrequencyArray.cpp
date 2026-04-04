#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        // Use arrays instead of maps for speed (constraints say nums[i] <= 10^5)
        int count[100001] = {0}; // frequency of each number
        int freq[100001] = {0};  // frequency of frequencies
        
        int max_f = 0;
        int distinct = 0;
        int res = 0;

        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            
            // Update the frequency buckets
            if (count[num] > 0) {
                freq[count[num]]--;
            } else {
                distinct++;
            }
            
            count[num]++;
            int f = count[num];
            freq[f]++;
            
            max_f = max(max_f, f);
            
            int L = i + 1; // Current prefix length
            
            // Condition 1: All elements are unique (e.g., 1, 2, 3, 4)
            if (max_f == 1) {
                res = L;
            }
            // Condition 2: All elements have the same frequency except one '1'
            // (e.g., 1, 1, 2, 2, 3) -> 2 * 2 + 1 = 5
            else if (freq[max_f] * max_f == L - 1 && freq[1] == 1) {
                res = L;
            }
            // Condition 3: One element has max_f, others have max_f - 1
            // (e.g., 1, 1, 2, 2, 2) -> 1 * 3 + (2-1) * 2 = 5
            else if ((freq[max_f - 1] + 1) * (max_f - 1) == L - 1 && freq[max_f] == 1) {
                res = L;
            }
            // Condition 4: Only one distinct element (e.g., 1, 1, 1, 1)
            else if (max_f == L) {
                res = L;
            }
        }

        return res;
    }
};
