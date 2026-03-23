class Solution {
public:
    string minRemoveToMakeValid(string s) {
       
                     
         int n = s.length();
         int count = 0;
         for(int i=0;i<n;i++){
            if(s[i] == '('){
                count++;
            }else if(s[i] == ')'){
                count--;
            }
            if(count < 0){
                s[i] = '*';
                count = 0;
            }
         }

        count = 0;
        for(int i = n-1;i>=0;i--){
            if(s[i] == ')'){
                count++;
            }else if(s[i] == '('){
                count--;
            }
            if(count < 0){
                s[i] = '#';
                count = 0;
            }
        }

        string result = "";
        for(int i=0;i<n;i++){
            if(s[i] != '*' && s[i] != '#'){
                result += s[i];
            }
        }
         return result;
         
    }
};
