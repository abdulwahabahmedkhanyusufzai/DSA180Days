#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    int n;

    // DFS to mark the island with a unique ID and calculate its size
    int dfs(int r, int c, int id, vector<vector<int>>& grid) {
        grid[r][c] = id;
        int size = 1;
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // If the neighbor is within bounds and is an unvisited part of the island ('1')
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                size += dfs(nr, nc, id, grid);
            }
        }
        return size;
    }

public:
    int largestIsland(vector<vector<int>>& grid) {
        n = grid.size();
        unordered_map<int, int> islandSizes;
        int islandId = 2; // Start IDs from 2
        int maxIsland = 0;

        // Step 1: Label all existing islands and record their sizes
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 1) {
                    int size = dfs(r, c, islandId, grid);
                    islandSizes[islandId] = size;
                    maxIsland = max(maxIsland, size);
                    islandId++;
                }
            }
        }

        // Step 2: Try converting every '0' to a '1'
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 0) {
                    unordered_set<int> neighborIslands;
                    
                    // Check all 4 directions for adjacent islands
                    for (int i = 0; i < 4; i++) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];
                        
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] >= 2) {
                            neighborIslands.insert(grid[nr][nc]);
                        }
                    }

                    // Calculate the size if we flipped this zero
                    int potentialSize = 1; 
                    for (int id : neighborIslands) {
                        potentialSize += islandSizes[id];
                    }
                    
                    maxIsland = max(maxIsland, potentialSize);
                }
            }
        }

        return maxIsland;
    }
};
