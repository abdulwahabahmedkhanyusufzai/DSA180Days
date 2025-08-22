#include <vector>

using namespace std;

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int zeroCount = 0;
        int n = arr.size();

       
        for (int x : arr) {
            if (x == 0) {
                zeroCount++;
            }
        }
        
        int i = n - 1;              
        int j = n - 1 + zeroCount; 

      while (i < j) {
            if (j < n) {
                arr[j] = arr[i];
            }
            if (arr[i] == 0) {
                j--;
                if (j < n) {
                    arr[j] = 0;
                }
            }
            i--;
            j--;
        }
    }
};