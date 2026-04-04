#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int mod = 1e9 + 7;
        
        // dp_score[r][c], dp_ways[r][c]
        vector<vector<int>> dp_score(n + 1, vector<int>(n + 1, -1));
        vector<vector<int>> dp_ways(n + 1, vector<int>(n + 1, 0));

        // Base case: Starting at the bottom-right 'S'
        dp_score[n - 1][n - 1] = 0;
        dp_ways[n - 1][n - 1] = 1;

        for (int r = n - 1; r >= 0; r--) {
            for (int c = n - 1; c >= 0; c--) {
                // Skip the starting 'S' (already initialized) and barriers 'X'
                if (board[r][c] == 'X' || board[r][c] == 'S') continue;

                // Check three directions: Down, Right, and Diagonal-Down-Right
                int directions[3][2] = {{r + 1, c}, {r, c + 1}, {r + 1, c + 1}};
                int max_s = -1;
                long long ways = 0;

                for (auto& d : directions) {
                    int nr = d[0], nc = d[1];
                    if (dp_score[nr][nc] > max_s) {
                        max_s = dp_score[nr][nc];
                        ways = dp_ways[nr][nc];
                    } else if (dp_score[nr][nc] == max_s && max_s != -1) {
                        ways = (ways + dp_ways[nr][nc]) % mod;
                    }
                }

                // If at least one path reaches this cell
                if (max_s != -1) {
                    int current_val = (board[r][c] == 'E') ? 0 : (board[r][c] - '0');
                    dp_score[r][c] = max_s + current_val;
                    dp_ways[r][c] = (int)ways;
                }
            }
        }

        if (dp_score[0][0] == -1) return {0, 0};
        return {dp_score[0][0], dp_ways[0][0]};
    }
};
