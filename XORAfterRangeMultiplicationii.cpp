class Solution {
    const int MOD = 1e9 + 7;

    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        // Lower the threshold slightly to balance the complexity
        int b = 150; 
        
        // We use a 2D vector for the difference arrays
        // diff[k][i] will store the multiplier for index i assuming stride k
        vector<vector<long long>> diff(b + 1, vector<long long>(n + b + 1, 1));

        for (auto& q : queries) {
            int li = q[0], ri = q[1], ki = q[2];
            long long vi = q[3];
            
            if (ki > b) {
                // Large K: Brute force
                for (int idx = li; idx <= ri; idx += ki) {
                    nums[idx] = (1LL * nums[idx] * vi) % MOD;
                }
            } else {
                // Small K: Multiplicative Difference Array
                diff[ki][li] = (diff[ki][li] * vi) % MOD;
                
                // Find the first index > ri that is in the sequence li + m*ki
                int next_idx = li + ((ri - li) / ki + 1) * ki;
                if (next_idx < n + b) {
                    diff[ki][next_idx] = (diff[ki][next_idx] * modInverse(vi)) % MOD;
                }
            }
        }

        // Consolidate Small K
        for (int k = 1; k <= b; ++k) {
            for (int r = 0; r < k; ++r) {
                long long current_multiplier = 1;
                for (int i = r; i < n; i += k) {
                    current_multiplier = (current_multiplier * diff[k][i]) % MOD;
                    if (current_multiplier != 1) {
                        nums[i] = (1LL * nums[i] * current_multiplier) % MOD;
                    }
                }
            }
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            result ^= nums[i];
        }

        return result;
    }
};
