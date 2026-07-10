/*
 * RUNNER: knapsack_allocator
 * SOURCE: 15_Dynamic_Programming/Knapsack/ProfitableSchemas.cpp  (included)
 *
 * Repurposes the DP knapsack pattern to solve worker-node resource packing:
 * Given N tasks each with (ram_mb, cpu_mcores, value) and a worker budget,
 * find the optimal subset to assign.
 *
 * The ProfitableSchemas.cpp uses the exact same 2D DP iteration pattern
 * (iterate backwards, dp[i][j] += dp[i-members][prevProfit]).
 * We apply it to (RAM, CPU) two-constraint knapsack.
 *
 * Protocol (stdin):
 *   Line 1: N W C  (tasks, ram_budget_MB, cpu_budget_mcores)
 *   Lines 2..N+1: <task_id> <ram_mb> <cpu_mc> <value>
 *
 * Output JSON:
 *   {"ok":true,"selected":["t1","t3"],"total_value":42,"ram_used":512,"cpu_used":800}
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// ── Include actual DP Knapsack file ─────────────────────────────────────────
// ProfitableSchemas uses dp[i][j] with backward iteration — same pattern here
#include "../../15_Dynamic_Programming/Knapsack/ProfitableSchemas.cpp"
// ─────────────────────────────────────────────────────────────────────────────

using namespace std;

int main() {
    int N, W, C;
    if (!(cin >> N >> W >> C)) { cout << "{\"ok\":false,\"error\":\"bad input\"}\n"; return 1; }

    vector<string> task_ids(N);
    vector<int> ram(N), cpu(N), val(N);
    for (int i = 0; i < N; i++) cin >> task_ids[i] >> ram[i] >> cpu[i] >> val[i];

    // 2D DP knapsack — mirrors ProfitableSchemas.cpp backward-iteration pattern
    // dp[w][c] = max value with w RAM and c CPU remaining
    vector<vector<int>> dp(W + 1, vector<int>(C + 1, 0));
    // Track choices for reconstruction
    vector<vector<vector<bool>>> chose(N, vector<vector<bool>>(W + 1, vector<bool>(C + 1, false)));

    for (int k = 0; k < N; k++) {
        // Iterate backwards (0/1 knapsack — same as ProfitableSchemas.cpp)
        for (int w = W; w >= ram[k]; w--) {
            for (int c = C; c >= cpu[k]; c--) {
                int candidate = dp[w - ram[k]][c - cpu[k]] + val[k];
                if (candidate > dp[w][c]) {
                    dp[w][c] = candidate;
                    chose[k][w][c] = true;
                }
            }
        }
    }

    // Backtrack to find selected tasks
    vector<string> selected;
    int w = W, c = C;
    int ram_used = 0, cpu_used = 0;
    for (int k = N - 1; k >= 0; k--) {
        if (chose[k][w][c]) {
            selected.push_back(task_ids[k]);
            ram_used += ram[k]; cpu_used += cpu[k];
            w -= ram[k]; c -= cpu[k];
        }
    }
    reverse(selected.begin(), selected.end());

    cout << "{\"ok\":true,\"total_value\":" << dp[W][C]
         << ",\"ram_used\":" << ram_used
         << ",\"cpu_used\":" << cpu_used
         << ",\"selected\":[";
    for (int i = 0; i < (int)selected.size(); i++) {
        if (i) cout << ",";
        cout << "\"" << selected[i] << "\"";
    }
    cout << "]}\n";
    return 0;
}
