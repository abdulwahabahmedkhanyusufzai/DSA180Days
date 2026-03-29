class Solution {
public:
  void solve(vector<string> &board, int row, vector<vector<string>> &ans) {
    if (row == board.size()) {
      ans.push_back(board);
      return;
    }
    for (int col = 0; col < board.size(); col++) {
      if (isSafe(board, row, col)) {
        board[row][col] = 'Q';
        solve(board, row + 1, ans);
        board[row][col] = '.';
      }
    }
  }
  bool isSafe(vector<string> &board, int row, int col) {
    for (int i = 0; i < row; i++) {
      if (board[i][col] == 'Q') {
        return false;
      }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
      if (board[i][j] == 'Q') {
        return false;
      }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < board.size(); i--, j++) {
      if (board[i][j] == 'Q') {
        return false;
      }
    }
    return true;
  }
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<string> board(n, string(n, '.'));
    solve(board, 0, ans);
    return ans;
  }
};