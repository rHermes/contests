/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
#include <cstddef>

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{

  struct NodeStat
  {
    std::size_t numNodes{ 0 };
    std::size_t sumNodes{ 0 };
    std::size_t numMatches{ 0 };
  };

  [[nodiscard]] NodeStat topDown(TreeNode* root)
  {
    NodeStat ret;
    ret.numNodes = 1;
    ret.sumNodes += static_cast<std::size_t>(root->val);
    if (root->left) {
      auto leftRet = topDown(root->left);
      ret.numNodes += leftRet.numNodes;
      ret.sumNodes += leftRet.sumNodes;
      ret.numMatches += leftRet.numMatches;
    }

    if (root->right) {
      auto rightRet = topDown(root->right);
      ret.numNodes += rightRet.numNodes;
      ret.sumNodes += rightRet.sumNodes;
      ret.numMatches += rightRet.numMatches;
    }

    std::size_t ourAverage = ret.sumNodes / ret.numNodes;
    if (ourAverage == static_cast<std::size_t>(root->val)) {
      ret.numMatches++;
    }

    return ret;
  }

public:
  int averageOfSubtree(TreeNode* root)
  {
    const auto ans = topDown(root);

    return static_cast<int>(ans.numMatches);
  }
};
