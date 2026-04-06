class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        // Keep track of the minimum dimensions seen so far
        int min_row = m;
        int min_col = n;
        
        // Find the intersection of all operations
        for (const auto& op : ops) {
            min_row = min(min_row, op[0]);
            min_col = min(min_col, op[1]);
        }
        
        // The area of the overlapping rectangle gives the count of max elements
        return min_row * min_col;
    }
};
