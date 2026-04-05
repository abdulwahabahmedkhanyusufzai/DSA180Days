#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        // Flatten the board into a string
        string start = "";
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                start += to_string(board[i][j]);
            }
        }
        
        string target = "123450";
        if (start == target) return 0;
        
        // Predefined valid swap indices for a 2x3 board flattened to 1D
        vector<vector<int>> neighbors = {
            {1, 3},       // 0 can swap with 1, 3
            {0, 2, 4},    // 1 can swap with 0, 2, 4
            {1, 5},       // 2 can swap with 1, 5
            {0, 4},       // 3 can swap with 0, 4
            {1, 3, 5},    // 4 can swap with 1, 3, 5
            {2, 4}        // 5 can swap with 2, 4
        };
        
        queue<pair<string, int>> q; // Stores {current_board_state, move_count}
        unordered_set<string> visited;
        
        q.push({start, 0});
        visited.insert(start);
        
        while (!q.empty()) {
            auto [curr, moves] = q.front();
            q.pop();
            
            // Find the index of the empty square ('0')
            int zero_idx = curr.find('0');
            
            // Try all possible swaps
            for (int next_idx : neighbors[zero_idx]) {
                string next_state = curr;
                swap(next_state[zero_idx], next_state[next_idx]);
                
                // If this is the target, we've found the shortest path
                if (next_state == target) {
                    return moves + 1;
                }
                
                // If it's a new state, add it to the queue
                if (visited.find(next_state) == visited.end()) {
                    visited.insert(next_state);
                    q.push({next_state, moves + 1});
                }
            }
        }
        
        // If the queue empties and we haven't found the target, it's impossible
        return -1;
    }
};
