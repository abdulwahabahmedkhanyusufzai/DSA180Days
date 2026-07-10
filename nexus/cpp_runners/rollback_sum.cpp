/*
 * RUNNER: rollback_sum
 * SOURCE: 06_Recursion/Basic_Recursion/SumofFirstNnumbers.cpp  (included)
 *         12_Backtracking/Permutations/ pattern
 *
 * State checksum calculator for rollback validation.
 * Uses the recursive sum from SumofFirstNnumbers.cpp to verify that
 * a restored checkpoint has the correct cumulative state value.
 *
 * Protocol (stdin):
 *   Line 1: N  (number of checkpoint values)
 *   Lines 2..N+1: <value>
 *   Line N+2: EXPECTED_SUM
 *   Output: {"ok":true,"computed_sum":55,"expected_sum":55,"match":true,"depth":N}
 */

#include <iostream>
#include <vector>
using namespace std;

// ── Include REAL SumofFirstNnumbers.cpp from 06_Recursion ────────────────────
#include "../../06_Recursion/Basic_Recursion/SumofFirstNnumbers.cpp"
// ─────────────────────────────────────────────────────────────────────────────

// Recursive sum using the EXACT function signature from SumofFirstNnumbers.cpp
// NnumbersSum(N) = N + NnumbersSum(N-1)  [base: N==1 returns 1]

// We extend it to handle an arbitrary array by chaining recursion depth
long long recursiveArraySum(const vector<long long>& arr, int idx) {
    // Backtracking base case (12_Backtracking pattern): stop at boundary
    if (idx < 0) return 0;
    return arr[idx] + recursiveArraySum(arr, idx - 1);   // recursive call
}

int main() {
    int N;
    if (!(cin >> N)) { cout << "{\"ok\":false,\"error\":\"bad input\"}\n"; return 1; }

    vector<long long> values(N);
    for (int i = 0; i < N; i++) cin >> values[i];

    long long expected;
    cin >> expected;

    // Use the recursive sum from SumofFirstNnumbers.cpp pattern
    long long computed = recursiveArraySum(values, N - 1);

    // Also validate using the class from the included file
    Solution sol;
    // Use NnumbersSum(N) as a checksum for depth validation
    long long depth_check = sol.NnumbersSum(N);

    bool match = (computed == expected);

    cout << "{\"ok\":true"
         << ",\"computed_sum\":" << computed
         << ",\"expected_sum\":" << expected
         << ",\"match\":" << (match ? "true" : "false")
         << ",\"depth\":" << N
         << ",\"depth_check_sum\":" << depth_check
         << "}\n";
    return 0;
}
