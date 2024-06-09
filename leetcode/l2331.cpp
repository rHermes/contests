#include <exception>
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
  static bool evaluateTree(TreeNode* root)
  {
    switch (root->val) {
      case 0:
        return false;
      case 1:
        return true;
      case 2:
        return evaluateTree(root->left) || evaluateTree(root->right);
      case 3:
        return evaluateTree(root->left) && evaluateTree(root->right);
      default:
        std::terminate();
    }
  }
};
