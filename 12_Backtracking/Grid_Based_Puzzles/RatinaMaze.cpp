class Solution {
public:
  void solve(vector<vector<int>> &maze, int row, int col,
             vector<vector<int>> &ans) {
    if (row == maze.size() - 1 && col == maze[0].size() - 1) {
      ans.push_back(maze);
      return;
    }
    for (int i = 0; i < maze.size(); i++) {
      for (int j = 0; j < maze[i].size(); j++) {
        if (maze[i][j] == 1) {
          maze[i][j] = 2;
          solve(maze, i + 1, j, ans);
          maze[i][j] = 1;
        }
      }
    }
  }
  vector<vector<int>> findPath(vector<vector<int>> &maze) {
    vector<vector<int>> ans;
    solve(maze, 0, 0, ans);
    return ans;
  }
};