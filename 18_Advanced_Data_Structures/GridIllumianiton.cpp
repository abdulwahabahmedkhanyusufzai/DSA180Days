#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        // Maps to store the count of lamps illuminating each line
        unordered_map<int, int> rows, cols, diag, antiDiag;
        // Set to store the unique coordinates of active lamps
        // Use long long to encode (r, c) into a single key: r * n + c
        set<pair<int, int>> activeLamps;

        for (auto& lamp : lamps) {
            int r = lamp[0];
            int c = lamp[1];
            if (activeLamps.insert({r, c}).second) {
                rows[r]++;
                cols[c]++;
                diag[r - c]++;
                antiDiag[r + c]++;
            }
        }

        vector<int> result;
        for (auto& query : queries) {
            int r = query[0];
            int c = query[1];

            // 1. Is the current cell illuminated?
            if (rows[r] > 0 || cols[c] > 0 || diag[r - c] > 0 || antiDiag[r + c] > 0) {
                result.push_back(1);
            } else {
                result.push_back(0);
            }

            // 2. Turn off lamps in the 3x3 area
            for (int i = r - 1; i <= r + 1; i++) {
                for (int j = c - 1; j <= c + 1; j++) {
                    if (i < 0 || i >= n || j < 0 || j >= n) continue;
                    
                    if (activeLamps.erase({i, j})) {
                        rows[i]--;
                        cols[j]--;
                        diag[i - j]--;
                        antiDiag[i + j]--;
                    }
                }
            }
        }

        return result;
    }
};
