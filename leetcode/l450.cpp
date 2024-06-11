#include <iostream>

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static TreeNode* deleteNode(TreeNode* root, const int key)
  {
    // Ok, so three scenarios here.
    if (!root)
      return root;

    if (root->val < key) {
      root->right = deleteNode(root->right, key);
      return root;
    }

    if (key < root->val) {
      root->left = deleteNode(root->left, key);
      return root;
    }

    if (!root->left) {
      return root->right;
    }
    if (!root->right) {
      return root->left;
    }

    auto cur = root->right;
    while (cur->left != nullptr)
      cur = cur->left;

    cur->left = root->left;
    return root->right;
  }
};
