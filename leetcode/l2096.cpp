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

class Solution
{
  // we could do this better, but no need. Once we find the end node, it's
  // good.

  static bool dfs(std::string& srcStr,
                  std::string& dstStr,
                  int startValue,
                  int destValue,
                  std::string& curStr,
                  TreeNode* cur)
  {
    if (cur->val == startValue) {
      srcStr = curStr;
      if (!dstStr.empty())
        return true;
    } else if (cur->val == destValue) {
      dstStr = curStr;
      if (!srcStr.empty())
        return true;
    }

    if (cur->left) {
      curStr.push_back('L');
      if (dfs(srcStr, dstStr, startValue, destValue, curStr, cur->left))
        return true;
      curStr.pop_back();
    }

    if (cur->right) {
      curStr.push_back('R');
      if (dfs(srcStr, dstStr, startValue, destValue, curStr, cur->right))
        return true;
      curStr.pop_back();
    }

    return false;
  }

public:
  static std::string getDirections(TreeNode* root, int startValue, int destValue)
  {
    // We can convert these two step sequences into each other. Because
    // either the path goes into us or it's completly in one of the
    // subtrees. if it goes through us, then we just replace everything
    // before it with `U`
    std::string pathStart;
    std::string pathEnd;
    std::string cur;

    dfs(pathStart, pathEnd, startValue, destValue, cur, root);

    std::size_t i = 0;
    for (; i < pathStart.size() && i < pathEnd.size() && pathStart[i] == pathEnd[i]; i++) {
    }

    return std::string(pathStart.size() - i, 'U') + pathEnd.substr(i);
  }
};
