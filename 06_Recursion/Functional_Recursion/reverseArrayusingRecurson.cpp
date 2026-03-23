#include <iostream>
using namespace std;

class Solution {
public:
    void reverse(int arr[], int n) {
        if (n <= 1) {
            return;
        }

        int temp = arr[0];
        arr[0] = arr[n - 1];
        arr[n - 1] = temp;

        reverse(arr + 1, n - 2);
    }
};