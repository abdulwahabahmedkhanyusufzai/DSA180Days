class Solution {
public:
  void solve(vector<vector<int>> &board, int row, int col, int moveCount) {
    if (moveCount == board.size() * board[0].size()) {
      return;
    }
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[i].size(); j++) {
        if (board[i][j] == 0) {
          board[i][j] = moveCount;
          solve(board, i + 1, j, moveCount + 1);
          board[i][j] = 0;
        }
      }
    }
  }
  vector<vector<int>> knightsTour(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    solve(board, 0, 0, 1);
    return board;
  }
};