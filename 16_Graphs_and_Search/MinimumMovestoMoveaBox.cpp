#include <vector>
#include <queue>
#include <set>
#include <tuple>

using namespace std;

class Solution {
    int rows, cols;
    int dr[4] = {0, 0, 1, -1};
    int dc[4] = {1, -1, 0, 0};

    bool isValid(int r, int c, const vector<vector<char>>& grid) {
        return r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != '#';
    }

    // Inner BFS: Can the player get from start to end without hitting the box?
    bool canReach(int pr, int pc, int tr, int tc, int br, int bc, const vector<vector<char>>& grid) {
        queue<pair<int, int>> q;
        q.push({pr, pc});
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        visited[pr][pc] = true;

        while (!q.empty()) {
            auto [curr_r, curr_c] = q.front(); q.pop();
            if (curr_r == tr && curr_c == tc) return true;

            for (int i = 0; i < 4; i++) {
                int nr = curr_r + dr[i], nc = curr_c + dc[i];
                if (isValid(nr, nc, grid) && !visited[nr][nc] && !(nr == br && nc == bc)) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        return false;
    }

public:
    int minPushBox(vector<vector<char>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        int pr, pc, br, bc, tr, tc;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 'S') { pr = r; pc = c; }
                else if (grid[r][c] == 'B') { br = r; bc = c; }
                else if (grid[r][c] == 'T') { tr = r; tc = c; }
            }
        }

        // State: {pushes, box_r, box_c, player_r, player_c}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({0, br, bc, pr, pc});

        // visited[box_r][box_c][player_r][player_c] is too big, use a set or encoded int
        set<tuple<int, int, int, int>> visited;
        visited.insert({br, bc, pr, pc});

        while (!pq.empty()) {
            auto curr = pq.top(); pq.pop();
            int pushes = curr[0], b_r = curr[1], b_c = curr[2], p_r = curr[3], p_c = curr[4];

            if (b_r == tr && b_c == tc) return pushes;

            for (int i = 0; i < 4; i++) {
                int nb_r = b_r + dr[i], nb_c = b_c + dc[i]; // New box position
                int tp_r = b_r - dr[i], tp_c = b_c - dc[i]; // Target player position to push

                if (isValid(nb_r, nb_c, grid) && isValid(tp_r, tp_c, grid)) {
                    if (visited.find({nb_r, nb_c, b_r, b_c}) == visited.end()) {
                        if (canReach(p_r, p_c, tp_r, tp_c, b_r, b_c, grid)) {
                            visited.insert({nb_r, nb_c, b_r, b_c});
                            pq.push({pushes + 1, nb_r, nb_c, b_r, b_c});
                        }
                    }
                }
            }
        }
        return -1;
    }
};
