#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        // Sort by end time ascending; if tied, sort by start time descending
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[1] == b[1]) {
                return a[0] > b[0];
            }
            return a[1] < b[1];
        });
        
        int ans = 0;
        int p1 = -1; // Second largest point in the set
        int p2 = -1; // Largest point in the set
        
        for (const auto& interval : intervals) {
            int start = interval[0];
            int end = interval[1];
            
            // The interval contains both p1 and p2
            if (start <= p1) {
                continue;
            }
            // The interval contains only p2
            else if (start <= p2) {
                ans += 1;
                p1 = p2;
                p2 = end;
            }
            // The interval contains neither p1 nor p2
            else {
                ans += 2;
                p1 = end - 1;
                p2 = end;
            }
        }
        
        return ans;
    }
};
