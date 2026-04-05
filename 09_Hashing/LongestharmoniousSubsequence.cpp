class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> freq;
        
        // Count the frequency of each number
        for (int num : nums) {
            freq[num]++;
        }
        
        int max_len = 0;
        
        // Iterate through the hash map
        for (auto it : freq) {
            int current_num = it.first;
            int current_count = it.second;
            
            // Check if the number + 1 exists in the map
            if (freq.count(current_num + 1)) {
                max_len = max(max_len, current_count + freq[current_num + 1]);
            }
        }
        
        return max_len;
    }
};
