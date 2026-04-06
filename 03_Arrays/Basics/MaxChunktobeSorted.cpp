#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;
        
        // Array to store the minimum value from the right side up to index i
        vector<int> minRight(n);
        minRight[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            minRight[i] = min(minRight[i + 1], arr[i]);
        }
        
        int chunks = 1; // At minimum, the entire array is 1 chunk
        int maxLeft = arr[0];
        
        // Iterate through the array to find valid chunk boundaries
        for (int i = 0; i < n - 1; i++) {
            maxLeft = max(maxLeft, arr[i]);
            
            // If the max on the left is less than or equal to the min on the right,
            // a chunk boundary can be safely drawn here.
            if (maxLeft <= minRight[i + 1]) {
                chunks++;
            }
        }
        
        return chunks;
    }
};
