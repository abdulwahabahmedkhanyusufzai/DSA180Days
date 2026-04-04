#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> heights(n, 0); // Stores the top height of each specific square
        vector<int> result(n, 0);  // Stores the running maximum height
        int current_max_height = 0;
        
        for (int i = 0; i < n; i++) {
            int left = positions[i][0];
            int side = positions[i][1];
            int right = left + side;
            
            int base_height = 0;
            
            // Check all previously dropped squares for horizontal overlap
            for (int j = 0; j < i; j++) {
                int prev_left = positions[j][0];
                int prev_right = prev_left + positions[j][1];
                
                // An overlap occurs if the max of the left bounds is STRICTLY LESS 
                // than the min of the right bounds. (Touching edges don't count)
                if (max(left, prev_left) < min(right, prev_right)) {
                    base_height = max(base_height, heights[j]);
                }
            }
            
            // Calculate the top height of the current square
            heights[i] = base_height + side;
            
            // Update the global maximum height seen so far
            current_max_height = max(current_max_height, heights[i]);
            result[i] = current_max_height;
        }
        
        return result;
    }
};
