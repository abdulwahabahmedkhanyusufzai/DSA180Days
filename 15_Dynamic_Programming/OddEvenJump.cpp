#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return n;

        // odd[i] means we can reach the end starting from i with an odd jump
        vector<bool> odd(n, false);
        vector<bool> even(n, false);
        
        // Base case: the last element is always a success
        odd[n - 1] = even[n - 1] = true;
        
        // Map to store {value, index} of elements we have already seen (to the right)
        map<int, int> valToIndex;
        valToIndex[arr[n - 1]] = n - 1;
        
        int result = 1; // Count the last element itself

        for (int i = n - 2; i >= 0; i--) {
            // Find target for Odd Jump: smallest value >= arr[i]
            auto itOdd = valToIndex.lower_bound(arr[i]);
            if (itOdd != valToIndex.end()) {
                odd[i] = even[itOdd->second];
            }

            // Find target for Even Jump: largest value <= arr[i]
            auto itEven = valToIndex.upper_bound(arr[i]);
            if (itEven != valToIndex.begin()) {
                // upper_bound gives first element > arr[i], so prev is <= arr[i]
                itEven--; 
                even[i] = odd[itEven->second];
            }

            // If we can reach the end starting with an odd jump, increment result
            if (odd[i]) result++;
            
            // Add current element to the map for future indices to the left
            valToIndex[arr[i]] = i;
        }

        return result;
    }
};
