class Solution {
public:
  Node *lowestCommonAncestor(Node *root, Node *p, Node *q) {
    if (root == nullptr || root == p || root == q) {
      return root;
    }
    Node *left = lowestCommonAncestor(root->left, p, q);
    Node *right = lowestCommonAncestor(root->right, p, q);
    if (left != nullptr && right != nullptr) {
      return root;
    }
    return left != nullptr ? left : right;
  }
};