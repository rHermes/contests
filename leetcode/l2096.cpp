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
  static bool solve(const TreeNode* root, std::string& path, const int dst)
  {
    if (root->val == dst) {
      return true;
    }

    if (root->left) {
      path.push_back('L');
      if (solve(root->left, path, dst)) {
        return true;
      }
      path.pop_back();
    }

    if (root->right) {
      path.push_back('R');
      if (solve(root->right, path, dst)) {
        return true;
      }
      path.pop_back();
    }

    return false;
  }

public:
  static std::string getDirections(const TreeNode* root, int startValue, int destValue)
  {
    std::string srcPath;
    solve(root, srcPath, startValue);

    std::string dstPath;
    solve(root, dstPath, destValue);

    // Just remove the prefix.
    std::size_t i = 0;
    while (i < srcPath.size() && i < dstPath.size() && srcPath[i] == dstPath[i]) {
      i++;
    }

    std::string out(srcPath.size() - i, 'U');
    out += dstPath.substr(i);

    return out;
  }
};
