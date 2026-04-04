#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>

using namespace std;

class MajorityChecker {
    unordered_map<int, vector<int>> indices;
    vector<int> a;
    mt19937 rng{random_device{}()};

public:
    MajorityChecker(vector<int>& arr) : a(arr) {
        for (int i = 0; i < arr.size(); i++) {
            indices[arr[i]].push_back(i);
        }
    }
    
    int query(int left, int right, int threshold) {
        // Try random candidates from the range
        for (int i = 0; i < 40; i++) {
            int randomIndex = uniform_int_distribution<int>(left, right)(rng);
            int candidate = a[randomIndex];
            
            // Check the frequency of this candidate in [left, right]
            const auto& pos = indices[candidate];
            auto it1 = lower_bound(pos.begin(), pos.end(), left);
            auto it2 = upper_bound(pos.begin(), pos.end(), right);
            
            if (distance(it1, it2) >= threshold) {
                return candidate;
            }
        }
        
        return -1;
    }
};
