#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<pair<double, int>> workers;

        // 1. Calculate ratio for each worker
        for (int i = 0; i < n; ++i) {
            workers.push_back({(double)wage[i] / quality[i], quality[i]});
        }

        // 2. Sort workers by their wage/quality ratio
        sort(workers.begin(), workers.end());

        double min_cost = 1e18; // Use a very large number
        int quality_sum = 0;
        priority_queue<int> max_heap; // To keep track of the k smallest qualities

        for (auto& worker : workers) {
            double ratio = worker.first;
            quality_sum += worker.second;
            max_heap.push(worker.second);

            // If we have more than k workers, remove the one with the highest quality
            if (max_heap.size() > k) {
                quality_sum -= max_heap.top();
                max_heap.pop();
            }

            // Once we have exactly k workers, calculate the cost
            if (max_heap.size() == k) {
                min_cost = min(min_cost, ratio * quality_sum);
            }
        }

        return min_cost;
    }
};
