#include <vector>
using namespace std;

class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    int n = nums.size();
    vector<int> result(n);
    int prefixProduct = 1;
    int suffixProduct = 1;
    for (int i = 1; i < n; i++) {
      prefixProduct *= nums[i - 1];
      result[i] = prefixProduct;
    }

    for (int i = n - 2; i >= 0; i--) {
      suffixProduct *= nums[i + 1];
      result[i] *= suffixProduct;
    }
    return result;
  }
};