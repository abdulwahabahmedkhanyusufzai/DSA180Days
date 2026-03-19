#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> countFrequencies(vector<int> &nums) {
    // Your code goes here
    unordered_map<int, int> freq_map;

    for (int num : nums) {
      freq_map[num]++;
    }

    vector<vector<int>> result;
    result.reserve(freq_map.size());

    for (auto const &[val, freq] : freq_map) {
      result.push_back({val, freq});
    }
    return result;
  }
};