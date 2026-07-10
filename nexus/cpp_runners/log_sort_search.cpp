/*
 * RUNNER: log_sort_search
 * SOURCE: 07_Sorting/ArrayPartition.cpp  +  11_Binary_Search/
 *
 * Log Parser: Given millions of timestamped execution logs,
 *   1. Sort by timestamp (uses sort() from 07_Sorting/ArrayPartition.cpp)
 *   2. Binary search to find exact crash millisecond (11_Binary_Search)
 *
 * Protocol (stdin):
 *   Line 1: N  (number of log entries)
 *   Lines 2..N+1: <timestamp_ms> <event_type>
 *   Line N+2: TARGET_TS  (timestamp to search for)
 *
 * Output JSON:
 *   {"ok":true,"sorted_count":N,"found":true,"index":42,"timestamp":1720617859123,"event":"CRASH"}
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// ── 07_Sorting: ArrayPartition.cpp uses std::sort — same call here ───────────
// sort(nums.begin(), nums.end()) → we use sort(logs.begin(), logs.end())
// ─────────────────────────────────────────────────────────────────────────────

struct LogEntry {
    long long timestamp_ms;
    string    event_type;
    bool operator<(const LogEntry& o) const { return timestamp_ms < o.timestamp_ms; }
};

// ── 11_Binary_Search: classic lower_bound binary search ─────────────────────
int binarySearchLog(const vector<LogEntry>& logs, long long target) {
    int lo = 0, hi = (int)logs.size() - 1, result = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (logs[mid].timestamp_ms == target) { result = mid; break; }
        else if (logs[mid].timestamp_ms < target) lo = mid + 1;
        else                                      hi = mid - 1;
    }
    return result;
}

int main() {
    int n;
    if (!(cin >> n)) { cout << "{\"ok\":false,\"error\":\"bad input\"}\n"; return 1; }

    vector<LogEntry> logs(n);
    for (int i = 0; i < n; i++) cin >> logs[i].timestamp_ms >> logs[i].event_type;

    long long target;
    cin >> target;

    // 07_Sorting: sort logs by timestamp
    sort(logs.begin(), logs.end());

    // 11_Binary_Search: find the target
    int idx = binarySearchLog(logs, target);

    if (idx == -1) {
        cout << "{\"ok\":true,\"sorted_count\":" << n
             << ",\"found\":false,\"target\":" << target << "}\n";
    } else {
        cout << "{\"ok\":true,\"sorted_count\":" << n
             << ",\"found\":true,\"index\":" << idx
             << ",\"timestamp\":" << logs[idx].timestamp_ms
             << ",\"event\":\"" << logs[idx].event_type << "\"}\n";
    }
    return 0;
}
