class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> unique_substr;
        int i = 0,n=s.length();
        int maxLen = 0;
        for(int j=0;j<n;j++){
           if(unique_substr.contains(s[j]) and unique_substr[s[j]]>=i){
             i = unique_substr[s[j]] + 1;
           } 
           unique_substr[s[j]] = j;
           maxLen = max(maxLen ,j - i +1);
        }
        return maxLen;
    }
};
