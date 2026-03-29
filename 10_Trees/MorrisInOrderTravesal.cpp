class Solution {
public:
  vector<int> inorderTraversal(Node *root) {
    vector<int> result;
    Node *current = root;
    while (current != nullptr) {
      if (current->left == nullptr) {
        result.push_back(current->val);
        current = current->right;
      } else {
        Node *predecessor = current->left;
        while (predecessor->right != nullptr && predecessor->right != current) {
          predecessor = predecessor->right;
        }
        if (predecessor->right == nullptr) {
          predecessor->right = current;
          current = current->left;
        } else {
          predecessor->right = nullptr;
          result.push_back(current->val);
          current = current->right;
        }
      }
    }
    return result;
  }
};