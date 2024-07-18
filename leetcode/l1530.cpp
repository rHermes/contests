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

  static void dfs(std::vector<std::string>& out, std::string& cur, TreeNode* root)
  {
    if (!root->left && !root->right) {
      out.push_back(cur);
      return;
    }

    if (root->left) {
      cur.push_back('L');
      dfs(out, cur, root->left);
      cur.pop_back();
    }

    if (root->right) {
      cur.push_back('R');
      dfs(out, cur, root->right);
      cur.pop_back();
    }
  }

public:
  static int countPairs(TreeNode* root, int distance)
  {
    std::vector<std::string> leaves;
    std::string cur;

    dfs(leaves, cur, root);

    for (const auto& leaf : leaves) {
      std::cout << leaf << "\n";
    }

    int ans = 0;
    const int N = leaves.size();
    for (int i = 0; i < N; i++) {
      const auto& a = leaves[i];
      for (int j = i + 1; j < N; j++) {
        const auto& b = leaves[j];

        std::size_t idx = 0;
        while (idx < a.size() && idx < b.size() && a[idx] == b[idx]) {
          idx++;
        }

        const int dist = (a.size() - idx) + (b.size() - idx);

        if (dist <= distance) {
          ans++;
        }
      }
    }

    return ans;
  }
};
