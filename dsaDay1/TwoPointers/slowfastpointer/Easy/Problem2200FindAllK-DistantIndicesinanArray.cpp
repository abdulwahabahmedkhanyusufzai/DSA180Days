
class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        int slow = 0, n = nums.size();
        vector<int> result;
        for (int fast = 0; fast < n; ++fast) {
            if(nums[fast]==key){
              int start = max(slow, fast-k); 
              int end = min(n-1, fast+k);
                while(slow<n && slow<fast-k) slow++;
                for(int i = start; i<=end; i++){
                    result.push_back(i);
                }
                slow = end+1;
                
            }
    }
    return result;
}
};
