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

    std::vector<int> out;
    std::vector<std::pair<const Node*, bool>> st;
    out.reserve(1000);
    st.reserve(1000);

    st.emplace_back(root, false);

    while (!st.empty()) {
      const auto [cur, terminal] = std::move(st.back());
      st.pop_back();
      if (terminal) {
        out.push_back(cur->val);
        continue;
      }

      st.emplace_back(cur, true);
      for (const auto& child : cur->children | std::views::reverse) {
        st.emplace_back(child, false);
      }
    }

    return out;
  }
};
