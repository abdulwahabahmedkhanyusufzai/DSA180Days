class Solution {
public:
    long long findTheArrayConcVal(vector<int>& nums) {
      long long concetenation_value = 0;
      int left = 0,right=nums.size()-1;

      while(left<=right){
        if(left==right){
            concetenation_value += nums[left];
        }else{
             long long s1 = nums[left];
             long long s2 = nums[right];

             long long temp = s2;
             long long power_of_ten = 1;
             while(temp > 0){
                temp /= 10;
                power_of_ten *= 10;
             }
             concetenation_value += s1 * power_of_ten + s2;
        }
        left++;
        right--;
      }
      return concetenation_value;
    }
};