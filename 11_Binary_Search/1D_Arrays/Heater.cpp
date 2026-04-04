#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
  int findRadius(vector<int> &houses, vector<int> &heaters) {
    // Sort the heaters to enable binary search
    sort(heaters.begin(), heaters.end());

    int max_radius = 0;

    for (int house : houses) {
      // Find the first heater positioned at or after the current house
      auto it = lower_bound(heaters.begin(), heaters.end(), house);

      int current_min_dist = INT_MAX;

      // 1. Distance to the heater on the right (or exactly at the house)
      if (it != heaters.end()) {
        current_min_dist = min(current_min_dist, *it - house);
      }

      // 2. Distance to the heater on the left
      if (it != heaters.begin()) {
        auto prev_it = it - 1;
        current_min_dist = min(current_min_dist, house - *prev_it);
      }

      // The overall radius needs to be large enough to cover this house
      max_radius = max(max_radius, current_min_dist);
    }

    return max_radius;
  }
};