#include <array>
#include <iostream>
#include <ranges>
#include <vector>

// Definition for a Node.
class Node
{
public:
  int val;
  std::vector<Node*> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, std::vector<Node*> _children)
  {
    val = _val;
    children = _children;
  }
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
  static constexpr std::vector<int> postorder(const Node* root)
  {
    if (!root) {
      return {};
    }

    // We use arrays, to prevent resizing in the loop. Can easily
    // be switched to vectors.
    constexpr int MAXN = 10001;
    std::array<int, MAXN> tmp;
    std::array<std::pair<const Node*, bool>, MAXN> st;
    int tmpIdx = 0;
    int stIdx = 0;

    st[stIdx++] = { root, false };

    while (0 < stIdx) {
      if (st[stIdx - 1].second) {
        tmp[tmpIdx++] = st[--stIdx].first->val;
      } else {
        const auto cur = st[stIdx - 1].first;
        st[stIdx - 1].second = true;

        for (const auto& child : cur->children | std::views::reverse) {
          st[stIdx++] = { child, false };
        }
      }
    }

    return { tmp.begin(), tmp.begin() + tmpIdx };
  }
};
