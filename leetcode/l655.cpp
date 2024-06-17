#include <iostream>
#include <string>
#include <vector>

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
  static int getHeight(TreeNode* root)
  {
    if (!root)
      return 0;

    return 1 + std::max(getHeight(root->left), getHeight(root->right));
  }

  static void placeNum(std::vector<std::vector<std::string>>& out,
                       const int maxHeight,
                       const int curPos,
                       const int height,
                       TreeNode* root)
  {
    if (!root)
      return;

    out[height][curPos] = std::to_string(root->val);

    if (height == maxHeight)
      return;

    const int offset = 1 << (maxHeight - (height)-1);
    placeNum(out, maxHeight, curPos - offset, height + 1, root->left);
    placeNum(out, maxHeight, curPos + offset, height + 1, root->right);
  }

public:
  static std::vector<std::vector<std::string>> printTree(TreeNode* root)
  {
    // we just need to know the max depth.
    const int maxHeight = getHeight(root) - 1;
    const int width = (1 << (maxHeight + 1)) - 1;

    std::vector<std::vector<std::string>> out(maxHeight + 1, std::vector<std::string>(width));
    const int midPos = width / 2;

    placeNum(out, maxHeight, midPos, 0, root);

    return out;
  }
};
