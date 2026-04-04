#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s = to_string(n);
        int L = s.length();
        int d_size = digits.size();
        int res = 0;

        // 1. Count numbers with fewer digits than n
        // If n = 100 (3 digits), we count all 1-digit and 2-digit numbers
        for (int i = 1; i < L; ++i) {
            res += pow(d_size, i);
        }

        // 2. Count numbers with exactly L digits
        for (int i = 0; i < L; ++i) {
            bool hasSameDigit = false;
            for (const string& d : digits) {
                if (d[0] < s[i]) {
                    // All combinations for the remaining (L - 1 - i) positions
                    res += pow(d_size, L - 1 - i);
                } else if (d[0] == s[i]) {
                    hasSameDigit = true;
                    break; // Move to the next position in n
                }
            }
            
            // If we couldn't find a digit <= s[i], no more L-length numbers can be formed
            if (!hasSameDigit) return res;
        }

        // 3. If we reached here, it means n itself can be formed
        return res + 1;
    }
};
