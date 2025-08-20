
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
      if(nums.empty()) return 0;
      int slow =0,n = nums.size();
        for(int fast =1;fast < n;fast++){
          if(nums[slow] != nums[fast]){
             slow++;
            nums[slow] = nums[fast];

          }
        }
        return slow+1;
    }
};
