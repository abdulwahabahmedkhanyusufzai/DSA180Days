#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int totalOnes = 0;
        for (int num : arr) if (num == 1) totalOnes++;

        // Case 1: No ones in the array
        if (totalOnes == 0) return {0, (int)arr.size() - 1};

        // Case 2: Ones not divisible by 3
        if (totalOnes % 3 != 0) return {-1, -1};

        int k = totalOnes / 3;
        int first = -1, second = -1, third = -1;
        int count = 0;

        // Find the start of each of the three blocks of k ones
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == 1) {
                count++;
                if (count == 1) first = i;
                if (count == k + 1) second = i;
                if (count == 2 * k + 1) third = i;
            }
        }

        // Compare the patterns starting from first, second, and third
        // They must match until the third pointer hits the end of the array
        while (third < arr.size()) {
            if (arr[first] == arr[second] && arr[second] == arr[third]) {
                first++;
                second++;
                third++;
            } else {
                return {-1, -1};
            }
        }

        // first-1 is the end of the first part, second is the end of the second part
        return {first - 1, second};
    }
};
