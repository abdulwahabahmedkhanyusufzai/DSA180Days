#include <stack>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> stockSpan(vector<int> &prices) {
    vector<int> spans(prices.size());
    stack<int> s;
    for (int i = 0; i < prices.size(); i++) {
      while (!s.empty() && prices[s.top()] <= prices[i]) {
        s.pop();
      }
      spans[i] = s.empty() ? i + 1 : i - s.top();
      s.push(i);
    }
    return spans;
  }
};