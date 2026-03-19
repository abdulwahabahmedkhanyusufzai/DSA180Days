#include <iostream>
#include <climits>
using namespace std;

int main(){
    int n=4;
    int dividend = 10,divisor=3;
    if(dividend == INT_MIN and divisor == -1){
        cout<<"Negative"<<endl;
        return INT_MAX;
    }
    int sign = (dividend<0) ^ (divisor < 0) ? -1 : 1;
    cout << "sign:" << sign << endl;
    long long  absDividend = abs((long long)dividend);
    cout << "absDivdend" << absDividend << endl;
    long long absDivisor = abs((long long)divisor);
    cout << "abDivisior" << absDivisor <<endl;
    int quotient = 0;

    while(absDividend >= absDivisor){
        long long temp = absDivisor;
        cout << "temp before loop" << temp <<endl;

        int i = 1;
        cout << "i before loop :" << i <<endl;

        while(absDividend >= (temp<<1)){
            temp <<= 1;
            cout << "temp after loop" << temp << endl;
            i<<=1;
            cout << "i after loop" << i << endl;

        }
        absDividend -= temp;
        cout << "absDivended" << absDividend << endl;
        quotient += i;
        cout << "quotient" << quotient << endl;
    }
    quotient *= sign;
    cout <<  quotient << endl;
    
}