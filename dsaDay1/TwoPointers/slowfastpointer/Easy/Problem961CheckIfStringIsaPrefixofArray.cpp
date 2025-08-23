class Solution {
public:
    bool isPrefixString(string s, vector<string>& words) {
        int slow = 0;
        for(int fast=0;fast<words.size();fast++){
          if(s.substr(slow,words[fast].size())==words[fast]){
              slow+=words[fast].size();
              if(slow==s.size()) return true;
          }else{
              return false;
          }

        }
        return false;
    }
};
