class Solution{
public:
    int longestSubstring(string &s, int k, int start, int end) {
        if(end - start < k) return 0;

        unordered_map<char,int> freq_map;
        for(int i = start; i < end; i++) freq_map[s[i]]++;

        for(int i = start; i < end; i++){
            if(freq_map[s[i]] < k){
                int left = longestSubstring(s, k, start, i);
                int right = longestSubstring(s, k, i+1, end);
                return max(left, right);
            }
        }
        return end - start; // all chars >= k
    }

    int longestSubstring(string s, int k) {
        return longestSubstring(s, k, 0, s.size());
    }
};
