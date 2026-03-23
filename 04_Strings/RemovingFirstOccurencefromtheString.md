
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

 int m = needle.length(),n=haystack.length();
for(int i = 0;i<=n-m;i++){
    if(haystack.substr(i,needle.length()) == needle){
       return i;
    }
}
return -1;

slightly optimize sol,luton class Solution {
public:
    int strStr(string haystack, string needle) {
int n = haystack.size(), m = needle.size();
for(int i = 0;i<= n-m;i++){
    int j = 0;
    while (j < m && haystack[i + j] == needle[j]) {
                j++;
            }
    if (j == m) return i;
}
return -1;
    }
};
Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
 

Constraints:

1 <= haystack.length, needle.length <= 104
haystack and needle consist of only lowercase English characters.


                 i 
//Build LPS Array
//Longest Possible suffix String
class Solution {
public:
haystack = "leetcode", needle = "leeto"
            i                    li 
            [0,0,0,0]
             l   i
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        if (m == 0) return 0;
        
        // Build LPS array
        vector<int> lps(m, 0);
        for (int i = 1, len = 0; i < m;) {
            if (needle[i] == needle[len]) {
                lps[i++] = ++len;
            } else if (len > 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        // KMP search
        for (int i = 0, j = 0; i < n;) {
            if (haystack[i] == needle[j]) {
                i++, j++;
                if (j == m) return i - m;
            } else if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
        return -1;
    }
};


haystack = "leetcode", needle = "leeto" 4 = lps[4-1]
                i                    j
m=3    lps= [0,0,0,0] 

int m = haystack.length(),n=needle.length();
vector<int> lps(m,0);
for(int i =1;len=0;i<n){
    if(haystack[i] == needle[len]){
    } lps[i++] = ++len;
}else if(len > 0){
    len = lps[len-1];
}else{
    i++;
}