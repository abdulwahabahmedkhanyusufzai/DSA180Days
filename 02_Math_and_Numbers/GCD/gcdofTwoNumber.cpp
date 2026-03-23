#include <iostream>

using namespace std;

class Solution {
public:
    int GCD(int n1,int n2) {
        // Euclidean algorithm for optimal O(log(min(n1, n2))) time complexity
        while (n2 != 0) {
            int temp = n2;
            n2 = n1 % n2;
            n1 = temp;
        }
        return n1;
    }
};