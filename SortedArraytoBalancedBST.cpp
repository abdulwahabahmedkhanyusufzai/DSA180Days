class Solution {
public:
  Node *sortedArrayToBST(vector<int> &nums) {
    if (nums.empty()) {
      return nullptr;
    }
    return sortedArrayToBSTHelper(nums, 0, nums.size() - 1);
  }
  Node *sortedArrayToBSTHelper(vector<int> &nums, int start, int end) {
    if (start > end) {
      return nullptr;
    }
    int mid = start + (end - start) / 2;
    Node *root = new Node(nums[mid]);
    root->left = sortedArrayToBSTHelper(nums, start, mid - 1);
    root->right = sortedArrayToBSTHelper(nums, mid + 1, end);
    return root;
  }
};