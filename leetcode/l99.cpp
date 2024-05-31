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

#include <iostream>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static constexpr TreeNode* fixIt(TreeNode* root, TreeNode* prev, TreeNode*& first, TreeNode*& second)
  {
    if (root->left) {
      prev = fixIt(root->left, prev, first, second);
    }

    if (prev && root->val <= prev->val) {
      if (first == nullptr) {
        first = prev;
      }
      second = root;
    }

    prev = root;

    if (root->right) {
      prev = fixIt(root->right, root, first, second);
    }

    return prev;
  }

public:
  static constexpr void recoverTree(TreeNode* root)
  {
    TreeNode* fa = nullptr;
    TreeNode* sc = nullptr;

    fixIt(root, nullptr, fa, sc);

    std::swap(fa->val, sc->val);
  }
};

int
main()
{
  return 0;
}
