class Solution {
public:
  void solve(vector<vector<char>> &board) {
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[i].size(); j++) {
        if (board[i][j] == '.') {
          for (char c = '1'; c <= '9'; c++) {
            if (isSafe(board, i, j, c)) {
              board[i][j] = c;
              solve(board);
              board[i][j] = '.';
            }
          }
          return;
        }
      }
    }
  }
  bool isSafe(vector<vector<char>> &board, int row, int col, char c) {
    for (int i = 0; i < board.size(); i++) {
      if (board[i][col] == c) {
        return false;
      }
    }
    for (int i = 0; i < board[row].size(); i++) {
      if (board[row][i] == c) {
        return false;
      }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
      if (board[i][j] == c) {
        return false;
      }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < board[row].size();
         i--, j++) {
      if (board[i][j] == c) {
        return false;
      }
    }
    return true;
  }
  void solveSudoku(vector<vector<char>> &board) { solve(board); }
};