class Solution {
public:
  void toSumTree(Node *root) {
    if (root == nullptr) {
      return;
    }
    toSumTree(root->left);
    toSumTree(root->right);
    root->val = root->left->val + root->right->val;
  }
}