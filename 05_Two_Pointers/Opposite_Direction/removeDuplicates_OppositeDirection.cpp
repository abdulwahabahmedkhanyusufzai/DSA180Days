#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j <=i; j++) {
                if (nums[i] != nums[j]) {
                    nums[i] = nums[j];
                }
            }
        }

        return nums.size();
    }
};

void runTest(vector<int> nums) {
    cout << "Input -> ";
    for (int x : nums) cout << x << " ";
    cout << endl;

    Solution sol;
    int newLength = sol.removeDuplicates(nums);

    

    cout << "New length: " << newLength << endl;
    cout << "Modified array: ";
    for (int i = 0; i < newLength; i++) cout << nums[i] << " ";
    cout << "\n\n";
}

int main() {

   
    // 🔹 Duplicates spread out
    runTest({0,0,1,1,1,2,2,3,3,4});

    return 0;
}

