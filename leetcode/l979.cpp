#include <cmath>
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
  static int distributeCoins(TreeNode* root)
  {
    int moves = 0;

    if (root->left) {
      moves += distributeCoins(root->left);
      if (root->left->val != 1) {
        moves += std::abs(root->left->val - 1);
        root->val += root->left->val - 1;
      }
    }

    if (root->right) {
      moves += distributeCoins(root->right);
      if (root->right->val != 1) {
        moves += std::abs(root->right->val - 1);
        root->val += root->right->val - 1;
      }
    }

    return moves;
  }
};

int
main()
{
  return 0;
}
