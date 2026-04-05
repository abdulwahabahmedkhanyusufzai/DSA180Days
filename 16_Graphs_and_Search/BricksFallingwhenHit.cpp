#include <vector>
#include <algorithm>

using namespace std;

// Disjoint Set Union (Union-Find) data structure
class DSU {
    vector<int> parent;
    vector<int> size;
public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] == x) return x;
        // Path compression
        return parent[x] = find(parent[x]); 
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            // Attach one root to the other and combine sizes
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
    }
    
    int getSize(int x) {
        return size[find(x)];
    }
};

class Solution {
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int R = grid.size();
        int C = grid[0].size();
        
        // Create a copy of the grid to represent the state after ALL hits are applied
        vector<vector<int>> currentGrid = grid;
        for (const auto& hit : hits) {
            currentGrid[hit[0]][hit[1]] = 0;
        }
        
        // DSU size is R*C + 1. The last index (R*C) acts as the "roof" node
        DSU dsu(R * C + 1);
        int roof = R * C;
        
        // Build the initial DSU with all surviving bricks
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (currentGrid[r][c] == 1) {
                    int index = r * C + c;
                    
                    // Connect top row directly to the roof
                    if (r == 0) {
                        dsu.unite(index, roof);
                    }
                    // Connect to the upper adjacent brick
                    if (r > 0 && currentGrid[r - 1][c] == 1) {
                        dsu.unite(index, (r - 1) * C + c);
                    }
                    // Connect to the left adjacent brick
                    if (c > 0 && currentGrid[r][c - 1] == 1) {
                        dsu.unite(index, r * C + c - 1);
                    }
                }
            }
        }
        
        vector<int> res(hits.size(), 0);
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Process the hits in reverse order
        for (int i = hits.size() - 1; i >= 0; --i) {
            int r = hits[i][0];
            int c = hits[i][1];
            
            // If there was no brick originally at this hit location, nothing falls
            if (grid[r][c] == 0) {
                continue;
            }
            
            int index = r * C + c;
            int prevRoofSize = dsu.getSize(roof);
            
            // Restore the brick
            currentGrid[r][c] = 1;
            
            // Connect it to the roof if it's in the first row
            if (r == 0) {
                dsu.unite(index, roof);
            }
            
            // Connect to adjacent bricks
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                
                if (nr >= 0 && nr < R && nc >= 0 && nc < C && currentGrid[nr][nc] == 1) {
                    dsu.unite(index, nr * C + nc);
                }
            }
            
            int currRoofSize = dsu.getSize(roof);
            
            // If the roof size increased, the newly attached bricks (minus the restored one) are the ones that fell
            if (currRoofSize > prevRoofSize) {
                res[i] = currRoofSize - prevRoofSize - 1;
            }
        }
        
        return res;
    }
};
