class Solution {
public:
    int fib(int n) {
        // Correct Base Case: 
        // If n is 0, return 0. If n is 1, return 1.
        if (n <= 1) {
            return n;
        }

        // Recursive Step
        return fib(n - 1) + fib(n - 2);
    }
};