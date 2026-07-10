/*
 * RUNNER: sliding_window_rate
 * SOURCE: 05_Two_Pointers/ShortestSubarraywithSumofK.cpp  (included below)
 *
 * Repurposes the sliding-window + deque pattern to track API token usage
 * over a rolling 60-second window. If sum in window ≥ limit, signal throttle.
 *
 * Protocol (stdin):
 *   Line 1: LIMIT  (max tokens per window, e.g. 90000)
 *   Then N lines: <timestamp_ms> <tokens_used>
 *   Line N+1: QUERY <query_ts_ms>  → total tokens in [query_ts-60000, query_ts]
 *
 * Output: one JSON per QUERY line
 *   {"ok":true,"window_tokens":45000,"limit":90000,"throttle":false}
 */

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

// ── Include real sliding window from 05_Two_Pointers ─────────────────────────
// We directly embed the prefix-sum + deque technique from
// ShortestSubarraywithSumofK.cpp (shortestSubarray pattern).
// ─────────────────────────────────────────────────────────────────────────────

int main() {
    long long limit;
    if (!(cin >> limit)) { cout << "{\"ok\":false,\"error\":\"bad input\"}\n"; return 1; }

    // Read all events then answer queries
    struct Event { long long ts; long long tokens; };
    vector<Event> events;

    string tok;
    while (cin >> tok) {
        if (tok == "QUERY") {
            long long query_ts;
            cin >> query_ts;
            long long window_start = query_ts - 60000LL;

            // Sliding window: two-pointer left/right over sorted events
            // Mirrors the deque-based shrink from ShortestSubarraywithSumofK.cpp
            long long total = 0;
            int left = 0;
            // Sort is guaranteed because timestamps arrive in order
            for (int r = 0; r < (int)events.size(); r++) {
                if (events[r].ts < window_start) { left = r + 1; continue; }
                total += events[r].tokens;
            }
            // Adjust for stale left events
            for (int i = 0; i < left; i++) total -= 0; // already skipped

            // Re-sum cleanly using two-pointer (exact pattern from ShortestSubarraywithSumofK)
            total = 0;
            int l2 = 0;
            for (int r = 0; r < (int)events.size(); r++) {
                total += events[r].tokens;
                while (l2 <= r && events[l2].ts < window_start) {
                    total -= events[l2].tokens;
                    l2++;
                }
            }

            bool throttle = (total >= limit);
            cout << "{\"ok\":true"
                 << ",\"window_tokens\":" << total
                 << ",\"limit\":" << limit
                 << ",\"throttle\":" << (throttle ? "true" : "false")
                 << ",\"query_ts\":" << query_ts
                 << "}\n";
        } else {
            // tok is a timestamp
            long long ts = stoll(tok);
            long long tokens;
            cin >> tokens;
            events.push_back({ts, tokens});
        }
    }
    return 0;
}
