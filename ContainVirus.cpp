#include <vector>
#include <set>

using namespace std;

class Solution {
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    int m, n;
    
    // DFS to explore an infected region, find threatened cells, and count required walls
    void dfs(int r, int c, vector<vector<int>>& grid, vector<vector<bool>>& visited, 
             vector<pair<int, int>>& region, set<pair<int, int>>& threat, int& walls) {
        
        visited[r][c] = true;
        region.push_back({r, c});
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                if (grid[nr][nc] == 1 && !visited[nr][nc]) {
                    // Continue exploring the infected region
                    dfs(nr, nc, grid, visited, region, threat, walls);
                } else if (grid[nr][nc] == 0) {
                    // An adjacent uninfected cell represents a threat and requires a wall
                    threat.insert({nr, nc});
                    walls++;
                }
            }
        }
    }

public:
    int containVirus(vector<vector<int>>& isInfected) {
        m = isInfected.size();
        n = isInfected[0].size();
        int totalWalls = 0;
        
        while (true) {
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            vector<vector<pair<int, int>>> regions;
            vector<set<pair<int, int>>> threats;
            vector<int> wallsCount;
            
            // 1. Find all infected regions and their threats
            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {
                    if (isInfected[r][c] == 1 && !visited[r][c]) {
                        vector<pair<int, int>> region;
                        set<pair<int, int>> threat;
                        int walls = 0;
                        
                        dfs(r, c, isInfected, visited, region, threat, walls);
                        
                        // Only care about regions that can actually spread
                        if (!threat.empty()) {
                            regions.push_back(region);
                            threats.push_back(threat);
                            wallsCount.push_back(walls);
                        }
                    }
                }
            }
            
            // If no regions are threatening any uninfected cells, we are done
            if (regions.empty()) {
                break;
            }
            
            // 2. Find the region that threatens the most uninfected cells
            int maxThreatIdx = 0;
            for (int i = 1; i < threats.size(); i++) {
                if (threats[i].size() > threats[maxThreatIdx].size()) {
                    maxThreatIdx = i;
                }
            }
            
            // 3. Build walls around the most threatening region (mark as 2)
            totalWalls += wallsCount[maxThreatIdx];
            for (auto& p : regions[maxThreatIdx]) {
                isInfected[p.first][p.second] = 2; // 2 represents 'contained'
            }
            
            // 4. Spread the virus for all other uncontained regions
            for (int i = 0; i < regions.size(); i++) {
                if (i != maxThreatIdx) {
                    for (auto& p : threats[i]) {
                        isInfected[p.first][p.second] = 1; 
                    }
                }
            }
        }
        
        return totalWalls;
    }
};
