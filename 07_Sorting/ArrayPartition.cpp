#include <algorithm>
#include <vector>


using namespace std;

class Solution {
public:
  int arrayPairSum(vector<int> &nums) {
    // Sort the array to place closest numbers next to each other
    sort(nums.begin(), nums.end());

    int max_sum = 0;

    // Iterate through the array, skipping by 2 to grab the minimum of each pair
    for (int i = 0; i < nums.size(); i += 2) {
      max_sum += nums[i];
    }

    return max_sum;
  }
};