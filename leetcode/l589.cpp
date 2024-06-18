#include <iostream>
#include <vector>

/*
 Definition for a Node.
 */
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
  static std::vector<int> preorder(Node* root)
  {
    if (!root)
      return {};

    std::vector<std::pair<Node*, int>> stack;
    stack.emplace_back(root, -1);

    std::vector<int> out;

    while (!stack.empty()) {
      auto& [cur, prevChild] = stack.back();
      if (prevChild == -1) {
        out.push_back(cur->val);
      }
      prevChild++;

      if (prevChild < static_cast<int>(cur->children.size())) {
        stack.emplace_back(cur->children[prevChild], -1);
      } else {
        stack.pop_back();
      }
    }

    return out;
  }
};
