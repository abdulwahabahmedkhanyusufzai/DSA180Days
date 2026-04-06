#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Optimization: If k is large enough to break every wall on the shortest possible path
        if (k >= rows + cols - 2) return rows + cols - 2;

        // queue stores {row, col, remaining_k, steps}
        queue<vector<int>> q;
        q.push({0, 0, k, 0});

        // visited[r][c] stores the maximum remaining_k seen at that cell
        // Initialized to -1 to indicate unvisited
        vector<vector<int>> visited(rows, vector<int>(cols, -1));
        visited[0][0] = k;

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            vector<int> curr = q.front();
            q.pop();

            int r = curr[0], c = curr[1], rem_k = curr[2], steps = curr[3];

            // Reached target
            if (r == rows - 1 && c == cols - 1) return steps;

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    int next_k = rem_k - grid[nr][nc];
                    
                    // If we have enough k to move and we've found a "better" way to this cell
                    if (next_k >= 0 && visited[nr][nc] < next_k) {
                        visited[nr][nc] = next_k;
                        q.push({nr, nc, next_k, steps + 1});
                    }
                }
            }
        }

        return -1;
    }
};
