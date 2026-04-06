#include <algorithm>
#include <numeric>
#include <string>
#include <vector>


using namespace std;

class Solution {
public:
  vector<int> survivedRobotsHealths(vector<int> &positions,
                                    vector<int> &healths, string directions) {
    int n = positions.size();

    // Array to keep track of the original indices
    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0);

    // Sort indices based on the robots' starting positions (left to right)
    sort(indices.begin(), indices.end(),
         [&](int a, int b) { return positions[a] < positions[b]; });

    // Stack to store the indices of surviving robots
    vector<int> stack;

    for (int i : indices) {
      if (directions[i] == 'R') {
        // Moving right, push to stack
        stack.push_back(i);
      } else {
        // Moving left, check for collisions
        bool survived = true;
        while (!stack.empty() && directions[stack.back()] == 'R') {
          int top_idx = stack.back();

          if (healths[top_idx] < healths[i]) {
            // Top robot is destroyed, current robot loses 1 health
            healths[i] -= 1;
            stack.pop_back();
          } else if (healths[top_idx] > healths[i]) {
            // Current robot is destroyed, top robot loses 1 health
            healths[top_idx] -= 1;
            survived = false;
            break;
          } else {
            // Both have equal health, both are destroyed
            stack.pop_back();
            survived = false;
            break;
          }
        }

        // If the left-moving robot survived all collisions, add it to the stack
        if (survived) {
          stack.push_back(i);
        }
      }
    }

    // Sort the surviving robots back to their original input order
    sort(stack.begin(), stack.end());

    // Extract the final healths
    vector<int> result;
    for (int idx : stack) {
      result.push_back(healths[idx]);
    }

    return result;
  }
};