class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();
        int ans = INT_MAX;

        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int landFinish = landStartTime[i] + landDuration[i];
                int finish = max(landFinish, waterStartTime[j]) + waterDuration[j];
                ans = min(ans, finish);
            }
        }

     
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                int waterFinish = waterStartTime[j] + waterDuration[j];
                int finish = max(waterFinish, landStartTime[i]) + landDuration[i];
                ans = min(ans, finish);
            }
        }

        return ans;
    }
};
