class Solution {
public:
  Node *buildTree(vector<int> &inorder, vector<int> &preorder) {
    unordered_map<int, int> map;
    for (int i = 0; i < inorder.size(); i++) {
      map[inorder[i]] = i;
    }
    return buildTreeHelper(inorder, preorder, 0, inorder.size() - 1, map);
  }
  Node *buildTreeHelper(vector<int> &inorder, vector<int> &preorder, int start,
                        int end, unordered_map<int, int> &map) {
    if (start > end) {
      return nullptr;
    }
    Node *root = new Node(preorder[0]);
    int mid = map[preorder[0]];
    preorder.erase(preorder.begin());
    root->left = buildTreeHelper(inorder, preorder, start, mid - 1, map);
    root->right = buildTreeHelper(inorder, preorder, mid + 1, end, map);
    return root;
  }
};