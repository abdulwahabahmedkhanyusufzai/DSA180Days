#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    // Helper function to check if two strings are similar
    bool isSimilar(const string& a, const string& b) {
        int diff = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a[i] != b[i]) {
                diff++;
                // If there are more than 2 differences, they cannot be similar
                if (diff > 2) return false;
            }
        }
        // Valid similarities have exactly 0 or 2 differences
        return diff == 0 || diff == 2;
    }

    // DSU Find with path compression
    int find(int i, vector<int>& parent) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i], parent);
    }

public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        vector<int> parent(n);
        
        // Initially, every string is in its own isolated group
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        int groups = n;

        // Compare every unique pair of strings
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isSimilar(strs[i], strs[j])) {
                    int rootI = find(i, parent);
                    int rootJ = find(j, parent);
                    
                    // If they belong to different groups, union them
                    if (rootI != rootJ) {
                        parent[rootI] = rootJ;
                        groups--; // Merging two groups reduces the total count by 1
                    }
                }
            }
        }

        return groups;
    }
};
