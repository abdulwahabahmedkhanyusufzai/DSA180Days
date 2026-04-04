#include <algorithm>
#include <string>
#include <vector>


using namespace std;

class Solution {
public:
  vector<string> findRelativeRanks(vector<int> &score) {
    int n = score.size();

    // Store pairs of {score, original_index}
    vector<pair<int, int>> score_idx;
    for (int i = 0; i < n; ++i) {
      score_idx.push_back({score[i], i});
    }

    // Sort in descending order based on the score
    sort(score_idx.rbegin(), score_idx.rend());

    vector<string> res(n);

    // Assign medals or numerical ranks based on sorted position
    for (int i = 0; i < n; ++i) {
      int original_index = score_idx[i].second;

      if (i == 0) {
        res[original_index] = "Gold Medal";
      } else if (i == 1) {
        res[original_index] = "Silver Medal";
      } else if (i == 2) {
        res[original_index] = "Bronze Medal";
      } else {
        res[original_index] = to_string(i + 1);
      }
    }

    return res;
  }
};