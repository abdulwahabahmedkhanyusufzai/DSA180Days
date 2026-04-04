#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        // Initialize res with the first element
        int res = nums[0];
        
        // Calculate the GCD of the entire array
        for (int num : nums) {
            res = gcd(res, num);
            
            // Optimization: if GCD reaches 1, we can stop early
            if (res == 1) return true;
        }
        
        return res == 1;
    }
    
private:
    // Helper function for GCD (built-in std::gcd is available in C++17)
    int gcd(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
};
