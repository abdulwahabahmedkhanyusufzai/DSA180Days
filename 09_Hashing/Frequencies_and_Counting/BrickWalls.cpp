#include <algorithm>
#include <unordered_map>
#include <vector>


using namespace std;

class Solution {
public:
  int leastBricks(vector<vector<int>> &wall) {
    // Change the key from int to long long to prevent overflow
    unordered_map<long long, int> edge_freq;
    int max_edges_aligned = 0;

    for (const auto &row : wall) {
      long long position = 0; // Use long long for the prefix sum

      for (int i = 0; i < row.size() - 1; ++i) {
        position += row[i];
        edge_freq[position]++;

        max_edges_aligned = max(max_edges_aligned, edge_freq[position]);
      }
    }

    return wall.size() - max_edges_aligned;
  }
};