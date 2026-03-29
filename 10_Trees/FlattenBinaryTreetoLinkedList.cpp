class Solution {
public:
  void flatten(Node *root) {
    if (root == nullptr) {
      return;
    }
    flatten(root->left);
    flatten(root->right);
    Node *temp = root->right;
    root->right = root->left;
    root->left = nullptr;
    while (root->right != nullptr) {
      root = root->right;
    }
    root->right = temp;
  }
};