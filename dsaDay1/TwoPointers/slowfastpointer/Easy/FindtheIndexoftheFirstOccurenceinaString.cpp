class Solution {
public:
    int strStr(string haystack, string needle) {
        int slow = 0,n = haystack.length(),m=needle.length();

        for(int fast = 0;fast<n;fast++){
        if(needle[slow] == haystack[fast]){
            slow++;
            if(slow==m){
                return fast - m + 1;
            }
        }else if(needle[slow]!=haystack[fast]){
            fast = fast-slow;
            slow = 0;
        }
        }
        return -1;
    }
};