class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int slow =0;
        for(int fast = 0;fast<typed.length();fast++){
            if(name[slow]==typed[fast]){
                slow++;
            }else{
              if(fast == 0 || typed[fast] != typed[fast-1]) return false;
            }
        }
        return (slow == name.length());
    }
};