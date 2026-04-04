#include <unordered_map>
#include <vector>


using namespace std;

class Solution {
public:
  int findPairs(vector<int> &nums, int k) {
    if (k < 0)
      return 0; // Absolute difference can't be negative

    unordered_map<int, int> freq_map;

    // Build the frequency map
    for (int num : nums) {
      freq_map[num]++;
    }

    int unique_pairs = 0;

    // Iterate through the unique numbers in the map
    for (auto const &[num, count] : freq_map) {
      if (k == 0) {
        // If k is 0, we need at least two identical numbers to form a pair
        if (count > 1) {
          unique_pairs++;
        }
      } else {
        // If k > 0, check if (num + k) exists in the map
        if (freq_map.count(num + k)) {
          unique_pairs++;
        }
      }
    }

    return unique_pairs;
  }
};