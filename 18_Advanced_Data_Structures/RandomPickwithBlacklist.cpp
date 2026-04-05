#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>

using namespace std;

class Solution {
private:
    unordered_map<int, int> mapping;
    int valid_len;

public:
    Solution(int n, vector<int>& blacklist) {
        int b_size = blacklist.size();
        valid_len = n - b_size;
        
        // Put all blacklisted numbers in a set for O(1) lookups
        unordered_set<int> blacklisted_set(blacklist.begin(), blacklist.end());
        
        int last = n - 1;
        
        for (int b : blacklist) {
            // We only need to remap blacklisted numbers that fall in the valid random range
            if (b < valid_len) {
                // Find a number from the end of the array that is NOT blacklisted
                while (blacklisted_set.count(last)) {
                    last--;
                }
                // Map the blacklisted number to this valid number
                mapping[b] = last;
                last--;
            }
        }
    }
    
    int pick() {
        // Pick a random number in the valid range
        int r = rand() % valid_len;
        
        // If it was a blacklisted number, return its mapped valid equivalent
        if (mapping.count(r)) {
            return mapping[r];
        }
        
        // Otherwise, it's a safe number, return it directly
        return r;
    }
};
