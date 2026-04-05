#include <vector>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size();
        // State: {row, col, orientation} -> 0: horizontal, 1: vertical
        // Using a 3D array for visited states to stay fast
        bool visited[100][100][2] = {false};
        
        // {row, col, orientation, steps}
        queue<vector<int>> q;
        q.push({0, 1, 0, 0}); 
        visited[0][1][0] = true;

        while (!q.size() == 0) {
            vector<int> curr = q.front();
            q.pop();

            int r = curr[0], c = curr[1], v = curr[2], steps = curr[3];

            // Target: Horizontal at (n-1, n-1)
            if (r == n - 1 && c == n - 1 && v == 0) return steps;

            // 1. Move Right
            if (v == 0) { // Horizontal
                if (c + 1 < n && grid[r][c + 1] == 0 && !visited[r][c + 1][0]) {
                    visited[r][c + 1][0] = true;
                    q.push({r, c + 1, 0, steps + 1});
                }
            } else { // Vertical
                if (c + 1 < n && grid[r][c + 1] == 0 && grid[r - 1][c + 1] == 0 && !visited[r][c + 1][1]) {
                    visited[r][c + 1][1] = true;
                    q.push({r, c + 1, 1, steps + 1});
                }
            }

            // 2. Move Down
            if (v == 0) { // Horizontal
                if (r + 1 < n && grid[r + 1][c] == 0 && grid[r + 1][c - 1] == 0 && !visited[r + 1][c][0]) {
                    visited[r + 1][c][0] = true;
                    q.push({r + 1, c, 0, steps + 1});
                }
            } else { // Vertical
                if (r + 1 < n && grid[r + 1][c] == 0 && !visited[r + 1][c][1]) {
                    visited[r + 1][c][1] = true;
                    q.push({r + 1, c, 1, steps + 1});
                }
            }

            // 3. Rotate Clockwise (Horizontal -> Vertical)
            if (v == 0 && r + 1 < n && c < n && grid[r + 1][c] == 0 && grid[r + 1][c - 1] == 0 && !visited[r + 1][c - 1][1]) {
                // Technically the head moves from (r, c) to (r+1, c-1)
                visited[r + 1][c - 1][1] = true;
                q.push({r + 1, c - 1, 1, steps + 1});
            }

            // 4. Rotate Counter-Clockwise (Vertical -> Horizontal)
            if (v == 1 && c + 1 < n && r < n && grid[r][c + 1] == 0 && grid[r - 1][c + 1] == 0 && !visited[r - 1][c + 1][0]) {
                visited[r - 1][c + 1][0] = true;
                q.push({r - 1, c + 1, 0, steps + 1});
            }
        }

        return -1;
    }
};
