#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <span>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

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
  long long kthLargestLevelSum(TreeNode* root, int k)
  {
    auto rawBuf = std::make_unique_for_overwrite<long long[]>(k);
    std::span<long long> buf(rawBuf.get(), k);

    std::ranges::fill(buf, -1);

    std::deque<TreeNode*> Q;
    Q.emplace_back(root);

    while (!Q.empty()) {
      const int levelLen = Q.size();
      long long levelSum = 0;
      for (int zz = 0; zz < levelLen; zz++) {
        auto cur = Q.front();
        Q.pop_front();
        levelSum += cur->val;

        if (cur->left)
          Q.emplace_back(cur->left);

        if (cur->right)
          Q.emplace_back(cur->right);
      }

      // We we are bigger than the current answer we want, we update the
      // sum
      if (buf[0] < levelSum) {
        std::ranges::pop_heap(buf, std::ranges::greater{});
        buf.back() = levelSum;
        std::ranges::push_heap(buf, std::ranges::greater{});
      }
    }

    return buf[0];
  }
};
