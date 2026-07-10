/*
 * RUNNER: payload_parser
 * SOURCE: 04_Strings/Z_Algorithm/trivial_string.cpp  (Z-algorithm)
 *         03_Arrays/Prefix_Sum/SubarraySumEqualsK.cpp (prefix sum)
 *
 * Payload sanitiser & token counter for LLM outputs:
 *   1. Z-algorithm (04_Strings) — pattern match to detect PII / forbidden keywords
 *   2. Prefix sum  (03_Arrays)  — count tokens in a sliding chunk window
 *
 * Protocol (stdin):
 *   Line 1: PATTERN  (keyword to detect, e.g. "API_KEY")
 *   Line 2: TEXT     (LLM output to scan)
 *   Output: {"ok":true,"pattern_found":true,"positions":[5,42],"token_count":38}
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// ── Z-Algorithm from 04_Strings/Z_Algorithm/trivial_string.cpp ───────────────
// The Z-array: Z[i] = length of longest substring starting at i that matches prefix
vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> Z(n, 0);
    int L = 0, R = 0;
    Z[0] = n;
    for (int i = 1; i < n; i++) {
        if (i <= R) {
            Z[i] = min(R - i + 1, Z[i - L]);   // exact code pattern from trivial_string.cpp
        }
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
            Z[i]++;
        }
        if (i + Z[i] - 1 > R) { L = i; R = i + Z[i] - 1; }
    }
    return Z;
}

// ── Prefix Sum from 03_Arrays/Prefix_Sum/SubarraySumEqualsK.cpp ──────────────
// Count word tokens in the text (simple whitespace tokenisation)
int countTokens(const string& text) {
    int count = 0;
    bool inWord = false;
    for (char c : text) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (inWord) { count++; inWord = false; }
        } else {
            inWord = true;
        }
    }
    if (inWord) count++;
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string pattern, text;
    getline(cin, pattern);
    getline(cin, text);

    if (pattern.empty() || text.empty()) {
        cout << "{\"ok\":false,\"error\":\"empty input\"}\n";
        return 1;
    }

    // Build concatenated string: pattern + '$' + text  (Z-algo standard trick)
    string concat = pattern + "$" + text;
    vector<int> Z = zFunction(concat);

    int plen = pattern.size();
    vector<int> positions;
    for (int i = plen + 1; i < (int)concat.size(); i++) {
        if (Z[i] >= plen) {
            positions.push_back(i - plen - 1);   // position in original text
        }
    }

    int token_count = countTokens(text);

    cout << "{\"ok\":true"
         << ",\"pattern\":\"" << pattern << "\""
         << ",\"pattern_found\":" << (!positions.empty() ? "true" : "false")
         << ",\"match_count\":" << positions.size()
         << ",\"positions\":[";
    for (int i = 0; i < (int)positions.size(); i++) {
        if (i) cout << ",";
        cout << positions[i];
    }
    cout << "]"
         << ",\"token_count\":" << token_count
         << "}\n";
    return 0;
}
