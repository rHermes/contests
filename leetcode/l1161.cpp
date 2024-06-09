/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <algorithm>
#include <vector>

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
public:
  int maxLevelSum(TreeNode* root)
  {
    std::vector<int> ans;
    dfs(root, ans);

    auto it = std::max_element(ans.begin(), ans.end());
    return static_cast<int>(std::distance(ans.begin(), it) + 1);
  }

  void dfs(TreeNode* root, std::vector<int>& ans, std::size_t level = 0)
  {
    if (ans.size() == level)
      ans.push_back(root->val);
    else
      ans[level] += root->val;

    if (root->left)
      dfs(root->left, ans, level + 1);
    if (root->right)
      dfs(root->right, ans, level + 1);
  }
};
