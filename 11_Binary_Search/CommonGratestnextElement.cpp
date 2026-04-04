#include <vector>

class Solution {
public:
    char nextGreatestLetter(std::vector<char>& letters, char target) {
        int left = 0;
        int right = letters.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (letters[mid] > target) {
                // The answer could be mid, or something to the left
                right = mid - 1;
            } else {
                // letters[mid] is <= target, so we must search to the right
                left = mid + 1;
            }
        }
        
        // If left goes out of bounds, it wraps around to 0
        return letters[left % letters.size()];
    }
};