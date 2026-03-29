class Solution {
public:
  bool isSubtree(Node *root, Node *subRoot) {
    if (root == nullptr) {
      return false;
    }
    if (isSameTree(root, subRoot)) {
      return true;
    }
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
  }
  bool isSameTree(Node *p, Node *q) {
    if (p == nullptr && q == nullptr) {
      return true;
    }
    if (p == nullptr || q == nullptr) {
      return false;
    }
    if (p->val != q->val) {
      return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
  }
}