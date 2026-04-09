class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), q = queries.size();
        const int MOD = 1e9 + 7;
        for (int i = 0; i < q; i++) {
            int li = queries[i][0];
            int ri = queries[i][1];
            int ki = queries[i][2];
            int vi = queries[i][3];

            int idx = li;
            while (idx <= ri) {
                long long numy = (1LL * nums[idx] * vi) % MOD;
                nums[idx] = numy;
                idx += ki;
            }
        }

        int result = 0;
        for (int num : nums) {
            result ^= num;
        }

        return result;
    }
};
