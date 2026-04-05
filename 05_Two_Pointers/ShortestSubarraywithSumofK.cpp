#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        // Use long long for prefix sums to avoid overflow
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        deque<int> dq; // Stores indices
        int min_len = n + 1;

        for (int i = 0; i <= n; i++) {
            // 1. Check if we found a valid subarray
            while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= k) {
                min_len = min(min_len, i - dq.front());
                dq.pop_front();
            }

            // 2. Maintain monotonicity (prefixSum[dq] should be increasing)
            while (!dq.empty() && prefixSum[i] <= prefixSum[dq.back()]) {
                dq.pop_back();
            }

            dq.push_back(i);
        }

        return min_len <= n ? min_len : -1;
    }
};
