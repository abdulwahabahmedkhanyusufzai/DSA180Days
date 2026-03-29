#include <vector>

using namespace std;

class Solution {
public:
  vector<int> topView(Node *root) {
    vector<int> result;
    if (root == nullptr) {
      return result;
    }
    queue<pair<Node *, int>> q;
    q.push({root, 0});
    unordered_map<int, int> map;
    while (!q.empty()) {
      Node *node = q.front().first;
      int hd = q.front().second;
      q.pop();
      if (map.find(hd) == map.end()) {
        map[hd] = node->val;
      }
      if (node->left) {
        q.push({node->left, hd - 1});
      }
      if (node->right) {
        q.push({node->right, hd + 1});
      }
    }
    for (auto it : map) {
      result.push_back(it.second);
    }
    return result;
  }
};