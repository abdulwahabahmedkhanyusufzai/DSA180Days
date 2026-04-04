#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        long long mod = 1e9 + 7;
        // dp[roll_idx][last_face][consecutive_count]
        // Using 16 for consecutive_count because rollMax[i] <= 15
        long long dp[5001][6][16] = {0};

        // Base case: First roll
        for (int j = 0; j < 6; j++) {
            dp[1][j][1] = 1;
        }

        for (int i = 1; i < n; i++) { // Current number of rolls
            for (int j = 0; j < 6; j++) { // Last face rolled
                for (int k = 1; k <= rollMax[j]; k++) { // Current consecutive count
                    if (dp[i][j][k] == 0) continue;

                    // Try rolling a new face
                    for (int next_f = 0; next_f < 6; next_f++) {
                        if (next_f == j) {
                            // Same face: check if we can roll it again
                            if (k < rollMax[next_f]) {
                                dp[i + 1][next_f][k + 1] = (dp[i + 1][next_f][k + 1] + dp[i][j][k]) % mod;
                            }
                        } else {
                            // Different face: reset consecutive count to 1
                            dp[i + 1][next_f][1] = (dp[i + 1][next_f][1] + dp[i][j][k]) % mod;
                        }
                    }
                }
            }
        }

        // Sum up all valid sequences of length n
        long long res = 0;
        for (int j = 0; j < 6; j++) {
            for (int k = 1; k <= rollMax[j]; k++) {
                res = (res + dp[n][j][k]) % mod;
            }
        }

        return (int)res;
    }
};
