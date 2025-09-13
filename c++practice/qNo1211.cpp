#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    long long zeroFilledSubarray(vector<int> &nums){
        long long int count = 0,count_zero=0;
    for (int num:nums){
        if (num != 0){
        count=0;
        }else{
            count++;
            count_zero += count;
        }
            }
             return count_zero; 
        } 
           
        };

int main(){
    vector<int> nums = {1, 3, 2, 0,9,0,0};
    Solution s1;
    long long int result = s1.zeroFilledSubarray(nums);
    cout<<result<<endl;
     return 0;
}