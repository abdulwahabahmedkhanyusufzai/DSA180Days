class Solution {
public:
    string addStrings(string num1, string num2) {
        //we cna take both strings as i and j poiner sof the end and seocndly we cna make a carry 0 and run a loop while these strings did not reach to first we cna add carrya dn then with do modulo and ater modulo tvide carryh and builkt an s what about it 
        int i = num1.size() - 1,j = num2.size()-1,carry=0;
        //i = 1 , j= 2,carry=0
        string ans = "";
        while(i>=0 || j>=0 || carry){//1,2,0
            if(i >= 0) carry += num1[i--] - '0';//1
            if(j >= 0) carry += num2[j--] - '0';//3
         
           ans.push_back('0'+carry%10);//4%10 =4 
           carry /=10;//0
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
