class Solution {
public:
  vector<string> binaryTreePaths(Node *root) {
    vector<string> result;
    if (root == nullptr) {
      return result;
    }
    binaryTreePathsHelper(root, "", result);
    return result;
  }
  void binaryTreePathsHelper(Node *root, string path, vector<string> &result) {
    if (root == nullptr) {
      return;
    }
    path += to_string(root->val);
    if (root->left == nullptr && root->right == nullptr) {
      result.push_back(path);
      return;
    }
    path += "->";
    binaryTreePathsHelper(root->left, path, result);
    binaryTreePathsHelper(root->right, path, result);
  }
};