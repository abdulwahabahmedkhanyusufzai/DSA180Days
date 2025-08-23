class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        sort(nums.begin(), nums.end());  
        int n = nums.size()-1;
        int left=0,right= n;
        double minAvg = DBL_MAX;

        while(left<right){
        double avg = (nums[left] + nums[right])/2.0;
        minAvg = min(minAvg,avg);
        left++;right--;
        }
        return minAvg;
    }
};