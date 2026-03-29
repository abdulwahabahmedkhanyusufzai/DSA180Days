class Solution {
public:
  vector<int> KLevel(Node *root, int k) {
    vector<int> result;
    if (root == nullptr) {
      return result;
    }
    queue<pair<Node *, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
      Node *node = q.front().first;
      int level = q.front().second;
      q.pop();
      if (level == k) {
        result.push_back(node->val);
      }
      if (node->left) {
        q.push({node->left, level + 1});
      }
      if (node->right) {
        q.push({node->right, level + 1});
      }
    }
    return result;
  }
}