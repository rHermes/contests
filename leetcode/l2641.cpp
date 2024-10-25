#include <deque>

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
class Solution
{
public:
  TreeNode* replaceValueInTree(TreeNode* root)
  {
    // Ok, let's try this with a BFS and prayers.

    // cur, sum to subtract from total.
    std::deque<TreeNode*> Q;
    int prevTotal = 0;
    Q.emplace_back(root);
    root->val = 0;

    while (!Q.empty()) {
      int curSize = Q.size();
      int nextTotal = 0;
      for (int zz = 0; zz < curSize; zz++) {
        const auto cur = Q.front();
        Q.pop_front();

        cur->val += prevTotal;

        // ok, if we have kids we push them in.
        int ourSum = 0;
        if (cur->left)
          ourSum += cur->left->val;
        if (cur->right)
          ourSum += cur->right->val;

        if (cur->left) {
          cur->left->val = -ourSum;
          Q.emplace_back(cur->left);
        }

        if (cur->right) {
          cur->right->val = -ourSum;
          Q.emplace_back(cur->right);
        }

        nextTotal += ourSum;
      }
      prevTotal = nextTotal;
    }

    return root;
  }
};
