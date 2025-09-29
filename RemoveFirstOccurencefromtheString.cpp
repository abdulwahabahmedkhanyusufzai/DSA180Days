#include <iostream>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
for(int i = 0;i< haystack.length();i++){
    if(haystack.substr(i,needle.length()) == needle){
       return i;
    }
}
return -1;
    }
};

int main(){
    Solution sol;
    string haystack = "sadbutsad";
    string needle = "sad";
    int index = sol.strStr(haystack,needle);
    cout << index << endl;
    string haystack2 = "leetcode";
    string needle2 = "leeto";
    int index2 = sol.strStr(haystack2,needle2);
    cout << index2 << endl;
    return 0;
}