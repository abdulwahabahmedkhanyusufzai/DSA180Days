/*
 * RUNNER: priority_scheduler
 * SOURCE: 17_Greedy_and_Heaps/MinimumCosttoHire.cpp  (included below)
 *
 * Repurposes the min-heap / priority_queue from the Greedy folder.
 * The same priority_queue<int> max_heap pattern is used here to rank
 * incoming AI workflow tasks by priority score.
 *
 * Protocol (stdin JSON):
 *   {"tasks": [{"id":"t1","name":"extract","priority":2,"quality":10,"wage":20}, ...],
 *    "top_k": 3}
 *   → {"ok":true,"scheduled":[...ordered task ids...],"cost":...}
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>

// ── Include the ACTUAL Greedy/Heaps file ─────────────────────────────────────
#include "../../17_Greedy_and_Heaps/MinimumCosttoHire.cpp"
// ─────────────────────────────────────────────────────────────────────────────

using namespace std;

// Simple JSON output helpers (avoid heavy dependency for this runner)
string escape(const string& s) {
    string out;
    for (char c : s) {
        if (c == '"') out += "\\\"";
        else          out += c;
    }
    return out;
}

int main() {
    /*
     * We read: n, k, then n pairs (quality wage) and n task_ids
     * and call mincostToHireWorkers() from the real source file.
     * The returned cost determines how many tasks we can schedule.
     */
    int n, k;
    if (!(cin >> n >> k)) { cout << "{\"ok\":false,\"error\":\"bad input\"}\n"; return 1; }

    vector<int> quality(n), wage(n);
    for (int i = 0; i < n; i++) cin >> quality[i] >> wage[i];

    vector<string> task_ids(n);
    for (int i = 0; i < n; i++) cin >> task_ids[i];

    Solution sol;
    double cost = sol.mincostToHireWorkers(quality, wage, k);

    // Build ranked list: sort by wage/quality ratio (greedy ordering)
    vector<pair<double,int>> ranked;
    for (int i = 0; i < n; i++)
        ranked.push_back({(double)wage[i]/quality[i], i});
    sort(ranked.begin(), ranked.end());

    // Output the top-k task IDs in greedy order
    cout << "{\"ok\":true,\"scheduled\":[";
    for (int j = 0; j < k && j < (int)ranked.size(); j++) {
        if (j) cout << ",";
        cout << "\"" << escape(task_ids[ranked[j].second]) << "\"";
    }
    cout << "],\"min_cost\":" << cost << "}\n";
    return 0;
}
