#include <array>
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

constexpr int MAXN = 100001;
class Solution
{
  static int solve(std::array<int, MAXN>& nodeDepths,
                   std::array<int, MAXN>& subtreeHeights,
                   std::array<int, MAXN>& firstLargestHeights,
                   std::array<int, MAXN>& secondLargestHeights,
                   TreeNode* const node,
                   int depth)
  {

    if (node == nullptr)
      return 0;

    nodeDepths[node->val] = depth;

    int leftHeight =
      solve(nodeDepths, subtreeHeights, firstLargestHeights, secondLargestHeights, node->left, depth + 1);
    int rightHeight =
      solve(nodeDepths, subtreeHeights, firstLargestHeights, secondLargestHeights, node->right, depth + 1);

    int currentHeight = 1 + std::max(leftHeight, rightHeight);

    subtreeHeights[node->val] = currentHeight;

    if (firstLargestHeights[depth] < currentHeight) {
      secondLargestHeights[depth] = firstLargestHeights[depth];
      firstLargestHeights[depth] = currentHeight;
    } else if (secondLargestHeights[depth] < currentHeight) {
      secondLargestHeights[depth] = currentHeight;
    }

    return currentHeight;
  }

public:
  static std::vector<int> treeQueries(TreeNode* const root, std::vector<int>& queries)
  {
    const int N = queries.size();
    std::array<int, MAXN> nodeDepths{};
    std::array<int, MAXN> subtreeHeights{};

    std::array<int, MAXN> firstLargestHeight{};
    std::array<int, MAXN> secondLargestHeight{};

    solve(nodeDepths, subtreeHeights, firstLargestHeight, secondLargestHeight, root, 0);

    // now then, we are going to be updating the max as we go upwards.
    std::vector<int> out(N);

    // ok, now then, we just have to work our way upwards.
    for (int i = 0; i < N; i++) {
      int Q = queries[i];

      int nodeLevel = nodeDepths[Q];

      if (subtreeHeights[Q] == firstLargestHeight[nodeLevel]) {
        out[i] = nodeLevel + secondLargestHeight[nodeLevel] - 1;
      } else {
        out[i] = nodeLevel + firstLargestHeight[nodeLevel] - 1;
      }
    }

    return out;
  }
};
