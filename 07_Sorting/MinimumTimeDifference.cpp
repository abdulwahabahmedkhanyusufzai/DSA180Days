#include <algorithm>
#include <climits>
#include <string>
#include <vector>


using namespace std;

class Solution {
public:
  int findMinDifference(vector<string> &timePoints) {
    // Pigeonhole principle: If there are more than 1440 time points,
    // there must be at least one duplicate, making the min difference 0.
    if (timePoints.size() > 1440)
      return 0;

    vector<int> mins;
    mins.reserve(timePoints.size());

    // Convert all time strings to total minutes past midnight
    for (const string &time : timePoints) {
      int h = stoi(time.substr(0, 2));
      int m = stoi(time.substr(3, 2));
      mins.push_back(h * 60 + m);
    }

    // Sort the times
    sort(mins.begin(), mins.end());

    int min_diff = INT_MAX;

    // Find the minimum difference between adjacent times
    for (int i = 1; i < mins.size(); ++i) {
      min_diff = min(min_diff, mins[i] - mins[i - 1]);
    }

    // Check the circular difference between the last and first time points
    int circular_diff = (mins[0] + 1440) - mins.back();
    min_diff = min(min_diff, circular_diff);

    return min_diff;
  }
};