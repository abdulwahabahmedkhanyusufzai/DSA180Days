#include <iostream>

using namespace std;

int main() {
    long long n;
    cout << "Enter a number to check if it is a palindrome: ";
    cin >> n;
    
    // Negative numbers are not palindromes (e.g., -121 reads as 121-)
    if (n < 0) {
        cout << n << " is not a palindrome number.\n";
        return 0;
    }

    long long rev = 0;
    long long temp = n;
    while (temp != 0) {
        int digit = temp % 10;
        rev = rev * 10 + digit;
        temp = temp / 10;
    }
    if (n == rev) {
        cout << n << " is a palindrome number.\n";
    } else {
        cout << n << " is not a palindrome number.\n";
    }
    return 0;
}