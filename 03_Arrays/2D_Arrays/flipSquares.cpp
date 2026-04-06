#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        int top = x;
        int bottom = x + k - 1;

        while (top < bottom) {
            for (int col = y; col < y + k; ++col) {
                swap(grid[top][col], grid[bottom][col]);
            }
            top++;
            bottom--;
        }

        return grid;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int x = 1, y = 1, k = 2;
    vector<vector<int>> result = sol.reverseSubmatrix(grid, x, y, k);

    cout << "Resulting Matrix:" << endl;
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}