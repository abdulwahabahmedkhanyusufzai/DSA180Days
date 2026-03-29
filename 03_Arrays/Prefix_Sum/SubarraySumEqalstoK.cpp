#include <vector>
using namespace std;
class Solution {
public:
  int subarraySum(vector<int> &nums, int k) {
    int n = nums.size();
    int count = 0;
    vector<int> prefixSum(n, 0);
    prefixSum[0] = nums[0];
    for (int i = 1; i < n; i++) {
      prefixSum[i] = prefixSum[i - 1] + nums[i];
    }

    unordered_map<int, int> mp;
    for (int j = 0; j < n; j++) {
      if (prefixSum[j] == k) {
        count++;
      }
      if (mp.count(prefixSum[j] - k)) {
        count += mp[prefixSum[j] - k];
      }
      mp[prefixSum[j]]++;
    }
    return count;
  }
};