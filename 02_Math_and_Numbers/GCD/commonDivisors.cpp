#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> divisors(int n) {
      vector<int> divisors;
      for(int i = 1; i * i <= n; i++){
        if (n % i == 0) {
            divisors.push_back(i);
            // Add the complementary divisor if it's not the exact square root
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
      }
      sort(divisors.begin(), divisors.end());
      return divisors;
    }
};