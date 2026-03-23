#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    bool isArmstrong(int n) {
     string s = to_string(n);
     int k = s.length();

     long long sum = 0;
     int temp = n;

     while(temp > 0){
        int digit = temp % 10;
        sum += pow(digit,k);
        temp /= 10;
     }
     return sum == n;
    }
};