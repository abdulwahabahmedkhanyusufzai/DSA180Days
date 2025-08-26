#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(string str){
    int left=0,right=str.length()-1;
    while(left<right){
        if(str[left] != str[right]) return false;
        left++;
        right--;
    }
    return true;
}


class Solution {
public:
    string longestPalindrome(string s) {
    string longest = "";
    for (int start = 0; start < s.length(); start++){
    for(int end=start;end<s.length();end++){   
        string sub = s.substr(start,end-start+1);
        if(isPalindrome(sub)&& sub.length() > longest.length()){
            longest = sub;
        }
    }
       
    }
    return longest;    
    }
};


int main(){
    string s = "babad";
    Solution s1;

    cout<<s1.longestPalindrome(s)<<endl;
    return 0;
}

