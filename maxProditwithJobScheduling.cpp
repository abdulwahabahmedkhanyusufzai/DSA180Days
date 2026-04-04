#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    int start, end, profit;
};

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<Job> jobs(n);
        for (int i = 0; i < n; i++) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }

        // 1. Sort jobs based on their end times
        sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.end < b.end;
        });

        // 2. dp[i] = max profit using the first i jobs (1-indexed for convenience)
        // dp[i].first = end time, dp[i].second = max profit
        vector<pair<int, int>> dp;
        dp.push_back({0, 0}); // Base case: time 0, profit 0

        for (const auto& job : jobs) {
            // 3. Find the latest job that finishes before the current job starts
            // We search for the first job whose end time is > current job's start time, 
            // then move back one step.
            auto it = upper_bound(dp.begin(), dp.end(), make_pair(job.start, 1000000000), 
                                  [](const pair<int, int>& a, const pair<int, int>& b) {
                                      return a.first < b.first;
                                  });
            
            int prev_profit = prev(it)->second;
            int current_total_profit = prev_profit + job.profit;

            // 4. If taking this job is better than the best we've seen so far, record it
            if (current_total_profit > dp.back().second) {
                dp.push_back({job.end, current_total_profit});
            }
        }

        return dp.back().second;
    }
};
