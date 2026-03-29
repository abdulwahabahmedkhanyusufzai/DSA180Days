class Solution {
public:
  int widthOfBinaryTree(Node *root) {
    if (root == nullptr) {
      return 0;
    }
    queue<pair<Node *, int>> q;
    q.push({root, 0});
    int maxWidth = 0;
    while (!q.empty()) {
      int size = q.size();
      int left = q.front().second;
      int right = q.back().second;
      maxWidth = max(maxWidth, right - left + 1);
      for (int i = 0; i < size; i++) {
        Node *node = q.front().first;
        int index = q.front().second;
        q.pop();
        if (node->left) {
          q.push({node->left, 2 * index});
        }
        if (node->right) {
          q.push({node->right, 2 * index + 1});
        }
      }
    }
    return maxWidth;
  }
}