#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
    int charToDigit[26];
    bool digitUsed[10];
    bool isLeadingChar[26];
    vector<char> uniqueChars;

public:
    bool isSolvable(vector<string>& words, string result) {
        if (result.length() < max_element(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.length() < b.length();
        })->length()) return false;

        fill(charToDigit, charToDigit + 26, -1);
        fill(digitUsed, digitUsed + 10, false);
        fill(isLeadingChar, isLeadingChar + 26, false);
        uniqueChars.clear();

        unordered_set<char> charSet;
        auto process = [&](string& s) {
            if (s.length() > 1) isLeadingChar[s[0] - 'A'] = true;
            for (char c : s) charSet.insert(c);
        };

        for (string& w : words) process(w);
        process(result);
        
        for (char c : charSet) uniqueChars.push_back(c);
        if (uniqueChars.size() > 10) return false;

        // Sorting chars can sometimes help, but weight-based sorting is better
        return backtrack(words, result, 0, 0, 0);
    }

private:
    bool backtrack(vector<string>& words, string& result, int charIdx, int colIdx, int carry) {
        // This is a simplified weight-based backtrack. 
        // For performance in "Hard" constraints, column-wise is usually required.
        // Let's implement the weight-based version for clarity:
        
        vector<long> weights(26, 0);
        for (string& w : words) {
            long p = 1;
            for (int i = w.length() - 1; i >= 0; i--) {
                weights[w[i] - 'A'] += p;
                p *= 10;
            }
        }
        long p = 1;
        for (int i = result.length() - 1; i >= 0; i--) {
            weights[result[i] - 'A'] -= p;
            p *= 10;
        }

        vector<int> activeChars;
        for(int i=0; i<26; ++i) if(weights[i] != 0 || isLeadingChar[i]) activeChars.push_back(i);
        // Add characters that might have 0 weight but are present (rare in this problem)
        
        return solve(activeChars, weights, 0, 0);
    }

    bool solve(const vector<int>& chars, const vector<long>& weights, int idx, long currentSum) {
        if (idx == chars.size()) return currentSum == 0;

        int c = chars[idx];
        for (int d = 0; d <= 9; d++) {
            if (digitUsed[d] || (d == 0 && isLeadingChar[c])) continue;

            digitUsed[d] = true;
            if (solve(chars, weights, idx + 1, currentSum + weights[c] * d)) return true;
            digitUsed[d] = false;
        }
        return false;
    }
};
