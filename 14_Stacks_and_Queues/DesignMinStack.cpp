#include <climits>
#include <stack>

using namespace std;
class Solution {
public:
  stack<long long> s;
  long long mini;
  MinStack() { mini = INT_MAX; }
  void push(int val) {
    if (s.empty()) {
      s.push(val);
      mini = val;
    } else if (val >= mini) {
      s.push(val);
    } else {
      s.push(2 * val - mini);
      mini = val;
    }
  }
  void pop() {
    if (s.empty())
      return;
    long long t = s.top();
    s.pop();
    if (t < mini) {
      mini = 2 * mini - t;
    }
  }
  int top() {
    if (s.empty())
      return -1;
    long long t = s.top();
    if (t < mini)
      return mini;
    return t;
  }
  int getMin() { return mini; }
};