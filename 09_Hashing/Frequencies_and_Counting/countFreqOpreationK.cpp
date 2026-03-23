#include <algorithm>
#include <vector>


using namespace std;

class Solution {
public:
  int maxFrequency(vector<int> &nums, int k) {
    // Sort the numbers to make the sliding window approach viable
    sort(nums.begin(), nums.end());

    long long left = 0;
    long long current_sum = 0;
    int max_freq = 0;

    for (int right = 0; right < nums.size(); ++right) {
      current_sum += nums[right];

      // If the cost to make all elements in the window equal to nums[right] > k
      // cost = (target_value * number_of_elements) - sum_of_elements
      while ((long long)nums[right] * (right - left + 1) - current_sum > k) {
        current_sum -= nums[left];
        left++;
      }

      // Update the maximum frequency found so far
      max_freq = max(max_freq, (int)(right - left + 1));
    }

    return max_freq;
  }
};