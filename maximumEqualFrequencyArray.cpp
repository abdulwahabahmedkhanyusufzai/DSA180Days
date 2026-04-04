#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        unordered_map<int, int> count; // num -> its frequency
        unordered_map<int, int> freq;  // frequency -> how many nums have it
        int max_len = 0;
        int distinct_elements = 0;

        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            int f = count[x];
            
            // If it already had a frequency, decrease the old frequency bucket
            if (f > 0) {
                freq[f]--;
            } else {
                distinct_elements++;
            }
            
            // Increase count and update the new frequency bucket
            count[x]++;
            f = count[x];
            freq[f]++;

            int current_prefix_len = i + 1;
            
            // Check the 4 Golden Rules
            // 1. All elements appear once
            if (freq[1] == current_prefix_len) {
                max_len = current_prefix_len;
            }
            // 2. Only one distinct element exists
            else if (freq[current_prefix_len] == 1) {
                max_len = current_prefix_len;
            }
            // 3. One element with freq 1, others with freq 'f'
            // Equation: 1 * 1 + (distinct - 1) * f == current_prefix_len
            else {
                // Find the frequency 'f' that isn't the outlier
                // We check if there's an element with frequency 1
                if (freq[1] == 1 && freq[f] * f == current_prefix_len - 1) {
                    max_len = current_prefix_len;
                }
                // 4. One element with freq 'f + 1', others with freq 'f'
                // Equation: 1 * (f + 1) + (distinct - 1) * f == current_prefix_len
                else if (freq[f] == 1 && freq[f - 1] * (f - 1) == current_prefix_len - f) {
                    max_len = current_prefix_len;
                }
                // Extra check for when 'f' is the outlier (larger than others)
                else if (freq[f+1] == 1 && freq[f] * f == current_prefix_len - (f + 1)) {
                    max_len = current_prefix_len;
                }
            }
        }

        return max_len;
    }
};
