#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n = status.size();
        vector<bool> hasBox(n, false);
        vector<bool> hasKey(n, false);
        vector<bool> used(n, false);
        
        queue<int> q;
        int totalCandies = 0;

        // Process initial boxes
        for (int b : initialBoxes) {
            hasBox[b] = true;
            // If it's already open or we somehow have the key, we can process it
            if (status[b] == 1) {
                q.push(b);
                used[b] = true;
            }
        }

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            totalCandies += candies[curr];

            // 1. Process keys found inside the current box
            for (int key : keys[curr]) {
                hasKey[key] = true;
                // If we already have the box and haven't opened it yet
                if (hasBox[key] && !used[key]) {
                    q.push(key);
                    used[key] = true;
                }
            }

            // 2. Process boxes found inside the current box
            for (int box : containedBoxes[curr]) {
                hasBox[box] = true;
                // If the box is openable (status is 1 or we have the key)
                if (!used[box] && (status[box] == 1 || hasKey[box])) {
                    q.push(box);
                    used[box] = true;
                }
            }
        }

        return totalCandies;
    }
};
