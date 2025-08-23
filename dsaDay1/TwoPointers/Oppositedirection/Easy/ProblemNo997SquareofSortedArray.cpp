#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        int pos = n-1;
        int left = 0,right = n-1;
        while(left<=right){
            int left_val = nums[left];
            int right_val = nums[right];

        if (abs(left_val) > abs(right_val)) {
            result[pos] = left_val * left_val;
            left++;
          }else{
            result[pos] = right_val * right_val;
            right--;
          }
          pos--;
        }
        return result;
    }
};