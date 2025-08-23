class Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        int slow = 0;
        int n = nums.size();
        for (int fast = 0; fast < n; fast++) {
             if (nums[fast] == 0) continue;
            if (fast < n - 1 && nums[fast] == nums[fast + 1]) {
                nums[slow++] = nums[fast] * 2;
                nums[fast + 1] = 0;
                fast++;
            } else if (nums[fast] != 0) {
                nums[slow++] = nums[fast];
            }
        }
        while (slow < n)
            nums[slow++] = 0;
        return nums;
    }
};