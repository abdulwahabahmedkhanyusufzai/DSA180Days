#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // 1. Directions: North, East, South, West
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        int x = 0, y = 0, di = 0; // Starting position and direction index

        // 2. Store obstacles in a hash set for fast lookup
        // We use a string or a long long to represent the coordinate pair
        unordered_set<string> obstacleSet;
        for (const auto& obs : obstacles) {
            obstacleSet.insert(to_string(obs[0]) + "," + to_string(obs[1]));
        }

        int maxDistSq = 0;

        // 3. Process commands
        for (int cmd : commands) {
            if (cmd == -2) { // Turn left
                di = (di + 3) % 4;
            } else if (cmd == -1) { // Turn right
                di = (di + 1) % 4;
            } else { // Move forward cmd units
                for (int i = 0; i < cmd; ++i) {
                    int nextX = x + dx[di];
                    int nextY = y + dy[di];
                    
                    // Check if the next position is an obstacle
                    if (obstacleSet.find(to_string(nextX) + "," + to_string(nextY)) == obstacleSet.end()) {
                        x = nextX;
                        y = nextY;
                        maxDistSq = max(maxDistSq, x * x + y * y);
                    } else {
                        // Hit an obstacle, stop moving for this command
                        break;
                    }
                }
            }
        }

        return maxDistSq;
    }
};