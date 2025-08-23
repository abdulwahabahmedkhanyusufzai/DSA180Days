class Solution {
public:
    bool isSubsequence(string s, string t) {
        int slow = 0;
        for (int fast = 0; fast < t.length(); fast++) {
            if (s[slow] == t[fast]) {
                slow++;
            }
        }
        return slow == s.length();
    }
};