#include <algorithm>
#include <random>
#include <vector>


class Solution {
private:
  std::vector<std::vector<int>> rects;
  std::vector<long long> prefix_sums;
  long long total_points;
  std::mt19937 rng; // Standard mersenne_twister_engine

public:
  Solution(std::vector<std::vector<int>> &rects)
      : rects(rects), total_points(0) {
    std::random_device rd;
    rng.seed(rd());

    for (const auto &rect : rects) {
      // Calculate points using long long to prevent integer overflow
      long long points =
          (long long)(rect[2] - rect[0] + 1) * (rect[3] - rect[1] + 1);
      total_points += points;
      prefix_sums.push_back(total_points);
    }
  }

  std::vector<int> pick() {
    // Pick a random target point out of all available points
    std::uniform_int_distribution<long long> dist(1, total_points);
    long long target = dist(rng);

    // Find the rectangle using binary search
    int rect_idx =
        std::lower_bound(prefix_sums.begin(), prefix_sums.end(), target) -
        prefix_sums.begin();
    const auto &rect = rects[rect_idx];

    // Pick random x and y uniformly within the chosen rectangle's boundaries
    std::uniform_int_distribution<int> distX(rect[0], rect[2]);
    std::uniform_int_distribution<int> distY(rect[1], rect[3]);

    return {distX(rng), distY(rng)};
  }
};