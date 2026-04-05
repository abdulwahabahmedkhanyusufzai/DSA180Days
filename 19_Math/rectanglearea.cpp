#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        long long mod = 1e9 + 7;

        // 1. Collect all unique x-coordinates and sort them
        set<int> x_coords;
        for (auto& rect : rectangles) {
            x_coords.insert(rect[0]);
            x_coords.insert(rect[2]);
        }

        vector<int> x_list(x_coords.begin(), x_coords.end());
        long long total_area = 0;

        // 2. Iterate through vertical strips defined by consecutive x-coordinates
        for (int i = 0; i < x_list.size() - 1; ++i) {
            int width = x_list[i+1] - x_list[i];
            if (width == 0) continue;

            // 3. Find all y-intervals that cover this specific vertical strip
            vector<pair<int, int>> y_intervals;
            for (auto& rect : rectangles) {
                if (rect[0] <= x_list[i] && rect[2] >= x_list[i+1]) {
                    y_intervals.push_back({rect[1], rect[3]});
                }
            }

            // 4. Merge overlapping y-intervals to find total covered height
            sort(y_intervals.begin(), y_intervals.end());
            long long covered_height = 0;
            int cur_y_start = -1;
            int cur_y_end = -1;

            for (auto& interval : y_intervals) {
                if (interval.first > cur_y_end) {
                    // New disjoint interval
                    covered_height += (cur_y_end - cur_y_start);
                    cur_y_start = interval.first;
                    cur_y_end = interval.second;
                } else {
                    // Extend the current merged interval
                    cur_y_end = max(cur_y_end, interval.second);
                }
            }
            // Add the last interval
            covered_height += (cur_y_end - cur_y_start);

            // 5. Area of this strip = width * total covered height
            total_area = (total_area + (long long)width * covered_height) % mod;
        }

        return (int)total_area;
    }
};
