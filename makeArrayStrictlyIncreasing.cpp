#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        // 1. Sort and unique arr2 for binary search
        sort(arr2.begin(), arr2.end());
        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());

        // dp[val] = min operations to have the current prefix end with 'val'
        map<int, int> dp;
        dp[-1] = 0; // Base case: before the first element

        for (int x : arr1) {
            map<int, int> next_dp;
            for (auto const& [prev_val, ops] : dp) {
                // Option 1: Keep arr1[i] if it's valid
                if (x > prev_val) {
                    if (next_dp.find(x) == next_dp.end() || next_dp[x] > ops) {
                        next_dp[x] = ops;
                    }
                }

                // Option 2: Replace arr1[i] with something from arr2
                auto it = upper_bound(arr2.begin(), arr2.end(), prev_val);
                if (it != arr2.end()) {
                    int replace_val = *it;
                    if (next_dp.find(replace_val) == next_dp.end() || next_dp[replace_val] > ops + 1) {
                        next_dp[replace_val] = ops + 1;
                    }
                }
            }
            if (next_dp.empty()) return -1;
            dp = next_dp;
        }

        int min_ops = 2001; // Max n is 2000
        for (auto const& [val, ops] : dp) {
            min_ops = min(min_ops, ops);
        }

        return min_ops;
    }
};
