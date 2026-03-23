#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int j = 0;
        for(int i=0;i<nums.size();i++){ //O(n)
            if(nums[i]!=val){
                nums[j] = nums[i];
                j++;
            }
        }
        return j;
    }
};

int main(){
    Solution sol;
    vector<int> nums = {3,2,2,3};
    int val = 3;
    int k = sol.removeElement(nums,val);
    
   for (int i = 0; i < k; i++) {
    cout << nums[i] << " ";
   }
   cout << endl;
   return 0;
}