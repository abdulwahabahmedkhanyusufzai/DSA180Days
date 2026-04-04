#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Min-heap storing {elevation, {row, col}}
        priority_queue<pair<int, pair<int, int>>, 
                       vector<pair<int, pair<int, int>>>, 
                       greater<pair<int, pair<int, int>>>> pq;
        
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        // Direction vectors for moving up, down, left, right
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};
        
        // Start at the top-left corner
        pq.push({grid[0][0], {0, 0}});
        visited[0][0] = true;
        
        int max_time = 0;
        
        while (!pq.empty()) {
            auto current = pq.top();
            pq.pop();
            
            int elevation = current.first;
            int r = current.second.first;
            int c = current.second.second;
            
            // The time required is the maximum elevation encountered so far
            max_time = max(max_time, elevation);
            
            // If we have reached the bottom-right corner, return the required time
            if (r == n - 1 && c == n - 1) {
                return max_time;
            }
            
            // Explore all 4 adjacent neighbors
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Ensure the neighbor is within bounds and hasn't been visited yet
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    pq.push({grid[nr][nc], {nr, nc}});
                }
            }
        }
        
        return -1; // Should never reach here given problem constraints
    }
};
