class Solution {
public:
    bool checkStrings(string s1, string s2) {
        int n = s1.length();
        // Frequency arrays for characters at even and odd indices
        vector<int> countEven1(26, 0), countOdd1(26, 0);
        vector<int> countEven2(26, 0), countOdd2(26, 0);

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                countEven1[s1[i] - 'a']++;
                countEven2[s2[i] - 'a']++;
            } else {
                countOdd1[s1[i] - 'a']++;
                countOdd2[s2[i] - 'a']++;
            }
        }

        // Compare the frequency counts
        return (countEven1 == countEven2) && (countOdd1 == countOdd2);
    }
};
