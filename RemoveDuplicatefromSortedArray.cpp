#include <iostream>
#include <vector>
using namespace std;

//O(n3) solution
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

for(int i = 0;i<nums.size();i++){
for(int j=0;j<=i+1;j++){
    if(nums[i] == nums[i+1]){
    nums.erase(nums.begin()+j);
     j--;
    }
}
   
}
return nums.size();
 }
};

//O(n2) solution
class Solution2 {
public:
    int removeDuplicates(vector<int>& nums) {

for(int i = 0;i<nums.size()-1;i++){
    if(nums[i] == nums[i+1]){
    nums.erase(nums.begin()+(i+1));
     i--;
    }
}
   return nums.size();
}

 };
//O(n) solution
class Solution3 {
public:
 int removeDuplicates(vector<int>& nums) {
 int j = 0;
for(int i = 0;i<nums.size();i++){
    if(nums[i] != nums[j]){
      j++;
      nums[j] = nums[i];
    }
}
   return j+1;
}
 };

int main(){
    Solution3 sol;
    vector<int> nums = {0,0,1,1,1,2,2,3,3,4};
    vector<int> expectedNums = {0,1,2,3,4}; // The expected answer with correct length
    int k = sol.removeDuplicates(nums);
    
   for (int i = 0; i < k; i++) {
    cout << nums[i] << " ";
}
  
  
  return 0;
}