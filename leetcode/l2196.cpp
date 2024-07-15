#include <iostream>
#include <unordered_map>
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
public:
  static TreeNode* createBinaryTree(const std::vector<std::vector<int>>& descriptions)
  {
    std::unordered_map<int, TreeNode*> data;
    // Each time we see an ID, we will xor it with the root.
    // at the end, the only time we see an ID once is for the root,
    // so it must be the root
    int root = 0;

    auto getNode = [&](const int val) -> TreeNode* {
      auto it = data.find(val);
      if (it != data.end()) {
        return it->second;
      }

      auto node = new TreeNode(val);
      data.emplace(val, node);
      root ^= val;
      return node;
    };

    for (const auto& desc : descriptions) {
      const auto parent = desc[0];
      const auto child = desc[1];
      const auto left = desc[2];

      auto parNode = getNode(parent);
      auto childNode = getNode(child);
      root ^= child;

      if (left) {
        parNode->left = childNode;
      } else {
        parNode->right = childNode;
      }
    }
    return data[root];
  }
};
