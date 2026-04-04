#include <vector>

using namespace std;

class Solution {
private:
    // All 8 adjacent directions (up, down, left, right, and 4 diagonals)
    int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int rows, cols;

    void dfs(vector<vector<char>>& board, int r, int c) {
        // Base case: Out of bounds or the cell is not an unrevealed empty square ('E')
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != 'E') {
            return;
        }

        int mine_count = 0;
        
        // Count how many mines are in the 8 adjacent cells
        for (auto& dir : dirs) {
            int nr = r + dir[0];
            int nc = c + dir[1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                if (board[nr][nc] == 'M') {
                    mine_count++;
                }
            }
        }

        if (mine_count > 0) {
            // If there are adjacent mines, reveal the number and stop exploring this path
            board[r][c] = '0' + mine_count;
        } else {
            // If there are no adjacent mines, mark as blank and recursively explore all 8 neighbors
            board[r][c] = 'B';
            for (auto& dir : dirs) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                dfs(board, nr, nc);
            }
        }
    }

public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        rows = board.size();
        cols = board[0].size();
        int r = click[0];
        int c = click[1];

        // 1. Clicked on a mine: Game Over
        if (board[r][c] == 'M') {
            board[r][c] = 'X';
            return board;
        }

        // 2. Clicked on an empty square: Start revealing
        dfs(board, r, c);
        
        return board;
    }
};