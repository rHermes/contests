#include <iostream>
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
  static void mm(std::vector<int>& ans, TreeNode* root, int& curMax, int& cur, int& curCount)
  {
    if (root->left) {
      mm(ans, root->left, curMax, cur, curCount);
    }

    if (cur != root->val) {
      if (curMax <= curCount) {
        if (curMax < curCount) {
          ans.clear();
          curMax = curCount;
        }
        ans.push_back(cur);
      }
      cur = root->val;
      curCount = 1;
    } else {
      curCount++;
    }

    if (root->right) {
      mm(ans, root->right, curMax, cur, curCount);
    }
  }

public:
  static std::vector<int> findMode(TreeNode* root)
  {
    std::vector<int> ans;

    int curMax = -1;
    int cur = -1000000000;
    int curCount = 0;
    mm(ans, root, curMax, cur, curCount);

    if (curMax <= curCount) {
      if (curMax < curCount) {
        ans.clear();
        curMax = curCount;
      }
      ans.push_back(cur);
    }
    return ans;
  }
};

int
main()
{
  return 0;
}
