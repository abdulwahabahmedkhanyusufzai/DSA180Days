#include <algorithm>
#include <random>
#include <vector>


using namespace std;

class Solution {
private:
  vector<int> prefix_sums;
  mt19937 rng; // Standard mersenne_twister_engine
  uniform_int_distribution<int> dist;

public:
  Solution(vector<int> &w) {
    int current_sum = 0;
    for (int weight : w) {
      current_sum += weight;
      prefix_sums.push_back(current_sum);
    }

    // Initialize the random number generator
    random_device rd;
    rng = mt19937(rd());

    // Set up the distribution range from 1 to the total sum
    dist = uniform_int_distribution<int>(1, current_sum);
  }

  int pickIndex() {
    // 1. Generate a random target
    int target = dist(rng);

    // 2. Use binary search to find the correct segment
    auto it = lower_bound(prefix_sums.begin(), prefix_sums.end(), target);

    // 3. Return the index of that segment
    return distance(prefix_sums.begin(), it);
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */