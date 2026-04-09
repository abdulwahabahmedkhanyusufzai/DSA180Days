class Solution {
public:
    int divide(int dividend, int divisor) {
        int sign = 1;
        if((dividend <0) ^ (divisor < 0)) sign = -1;
        long long s_dividend = (long long) dividend,s_divisor = (long long) divisor;
        long long abs_dividend = abs(s_dividend),abs_divisor = abs(s_divisor);
       
       long long result = 0;
        while(abs_dividend >= abs_divisor){
            long long count = 1;
            long long temp = abs_divisor;

            while(abs_dividend >= (temp<<1)){
                temp <<= 1;
                count <<=1;
            }
            abs_dividend -=temp;
            result += count;
        }

        long long final_result = result * sign;

        if(final_result > INT_MAX){
            return INT_MAX;
        }if(final_result < INT_MIN){
            return INT_MIN;
        }
        return (int) final_result;
    }
};
