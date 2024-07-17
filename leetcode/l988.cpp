#include <algorithm>
#include <iostream>
#include <string>

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
  static constexpr void solve(std::string& bestPath, std::string& currentPath, TreeNode* root)
  {
    if (!root->left && !root->right) {
      if (std::lexicographical_compare(currentPath.rbegin(), currentPath.rend(), bestPath.rbegin(), bestPath.rend())) {
        bestPath = currentPath;
      }
    }

    if (root->left) {
      currentPath.push_back('a' + root->left->val);
      solve(bestPath, currentPath, root->left);
      currentPath.pop_back();
    }

    if (root->right) {
      currentPath.push_back('a' + root->right->val);
      solve(bestPath, currentPath, root->right);
      currentPath.pop_back();
    }
  }

public:
  static constexpr std::string smallestFromLeaf(TreeNode* root)
  {
    std::string bestPath;
    bestPath.push_back('z' + 1);

    std::string currentPath;
    currentPath.push_back('a' + root->val);

    solve(bestPath, currentPath, root);
    std::ranges::reverse(bestPath);
    return bestPath;
  }
};
