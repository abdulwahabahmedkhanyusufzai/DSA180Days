#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        int revNumber = 0;
        while(x != 0){
            int digit = x % 10;
            if(revNumber  > INT_MAX / 10 || (revNumber == INT_MAX / 10 && digit > 7)) return 0;
            if(revNumber < INT_MIN /10 || (revnumber == INT_MIN /10 && digit < -8)) return 0;
            revNumber = revNumber * 10 + digit;
            x /= 10;
        }
        return revNumber;
    }
};

int main() {
    int n;
    cout << "Enter a number to reverse: ";
    cin >> n;
    long long rev = 0;
    while (n != 0) {
        int digit = n % 10;
        rev = rev * 10 + digit;
        n = n / 10;
    }
    
    if (rev > INT_MAX || rev < INT_MIN) {
        cout << "Reversed number: 0\n";
    } else {
        cout << "Reversed number: " << rev << endl;
    }
    return 0;
}