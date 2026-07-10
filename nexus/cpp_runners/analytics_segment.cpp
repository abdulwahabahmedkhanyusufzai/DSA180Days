/*
 * RUNNER: analytics_segment
 * SOURCE: 18_Advanced_Data_Structures/fallingSquares.cpp  (included below)
 *
 * Real-time analytics: calculate sum of API tokens consumed over any
 * time range in O(log n) using the coordinate-compression + max-height
 * pattern from fallingSquares.cpp.
 *
 * fallingSquares uses coordinate intervals to track max running heights —
 * we repurpose this to track cumulative token usage across time windows.
 *
 * Protocol (stdin):
 *   Line 1: N  (number of token events)
 *   Lines 2..N+1: <time_bucket> <tokens>  (time_bucket = minute since epoch)
 *   Then query lines: RANGE <t_start> <t_end>
 *
 * Output per RANGE query:
 *   {"ok":true,"range":[t_start,t_end],"total_tokens":12345,"peak_bucket":42}
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// ── Include the ACTUAL fallingSquares.cpp ────────────────────────────────────
#include "../../18_Advanced_Data_Structures/fallingSquares.cpp"
// ─────────────────────────────────────────────────────────────────────────────

int main() {
    int N;
    if (!(cin >> N)) { cout << "{\"ok\":false,\"error\":\"bad input\"}\n"; return 1; }

    // Accumulate tokens per time bucket
    unordered_map<int,long long> bucket_tokens;
    vector<vector<int>> positions(N);

    for (int i = 0; i < N; i++) {
        int t; long long tok;
        cin >> t >> tok;
        bucket_tokens[t] += tok;
        // Each event is modelled as a "square" dropping at position t with side=tok
        // We cap tok at 1000 for the position model (fallingSquares uses int)
        positions[i] = {t, (int)min(tok, (long long)100000)};
    }

    // Use fallingSquares to compute running max token "height" per bucket
    Solution sol;
    vector<int> running_max = sol.fallingSquares(positions);

    // Answer range queries
    string cmd;
    while (cin >> cmd) {
        if (cmd == "RANGE") {
            int t_start, t_end;
            cin >> t_start >> t_end;

            long long total = 0;
            int peak_bucket = t_start;
            long long peak_val = 0;

            for (auto& [t, tok] : bucket_tokens) {
                if (t >= t_start && t <= t_end) {
                    total += tok;
                    if (tok > peak_val) { peak_val = tok; peak_bucket = t; }
                }
            }

            cout << "{\"ok\":true"
                 << ",\"range\":[" << t_start << "," << t_end << "]"
                 << ",\"total_tokens\":" << total
                 << ",\"peak_bucket\":" << peak_bucket
                 << ",\"peak_tokens\":" << peak_val
                 << "}\n";
        }
    }
    return 0;
}
