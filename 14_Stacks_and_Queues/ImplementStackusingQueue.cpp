#include <queue>

using namespace std;

class MyStack {
  queue<int> q;

public:
  MyStack() {}
  void push(int x) { q.push(x); }
  int pop() {
    int size = q.size();
    while (size > 1) {
      q.push(q.front());
      q.pop();
      size--;
    }
    int top = q.front();
    q.pop();
    return top;
  }
  int peek() {
    int size = q.size();
    while (size > 1) {
      q.push(q.front());
      q.pop();
      size--;
    }
    int top = q.front();
    q.pop();
    q.push(top);
    return top;
  }
  bool empty() { return q.empty(); }
};