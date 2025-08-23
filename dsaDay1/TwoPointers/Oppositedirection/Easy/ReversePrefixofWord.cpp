class Solution {
public:
    string reversePrefix(string word, char ch) {
       if(!s.find(ch)) return word;
       int left=0;right=s.find(ch);

       while(left<right){
         swap(s[left],s[right]);
         left++;right--;
       }
       return word; 
    }
};