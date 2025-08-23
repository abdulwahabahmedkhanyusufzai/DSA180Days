
class Solution {
public:
     bool isPalindrome(string str){
        int left = 0, right = str.length() -1;
        while(left < right){
            if(str[left] != str[right]){
                return false;
            }
            left++;
            right--;
        }
        return true;
     }    
string firstPalindrome(vector<string>& words) {
  int slow =0;    
  for(int fast=0;fast<words.size();fast++){
    slow = fast;       
    string str = words[slow];
            if(isPalindrome(str)){
                return str;
            }
    }
    return "";
}
};
