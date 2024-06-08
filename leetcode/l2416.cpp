#include <array>
#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{

  struct TrieNode
  {
    int children{ 0 };
    std::array<int, 26> data{};
  };

  static int trieInsert(std::vector<TrieNode>& tree, int root, const std::string& str, const int idx)
  {
    auto node = &tree[root];
    node->children++;

    if (static_cast<int>(str.size()) == idx)
      return root;

    const int next = str[idx] - 'a';

    if (node->data[next] == 0)
      if (tree[root].data[next] == 0) {
        node->data[next] = tree.size();
        tree.emplace_back();
        node = &tree[root];
      }

    return trieInsert(tree, node->data[next], str, idx + 1);
  }

  static void triePushDown(std::vector<TrieNode>& tree, int root, int above)
  {
    auto& node = tree[root];

    node.children += above;

    for (int i = 0; i < 26; i++) {
      if (node.data[i] != 0)
        triePushDown(tree, node.data[i], node.children);
    }
  }

public:
  static std::vector<int> sumPrefixScores(const std::vector<std::string>& words)
  {
    const int N = words.size();

    // we are doing this with a vector instead of pointers, because it
    // performs a lot better. This just shows that cache locality is the
    // most important thing.
    std::vector<TrieNode> tree;
    tree.reserve(100);
    tree.emplace_back();
    int root = 0;

    std::vector<int> nodes(N);
    for (int i = 0; i < N; i++) {
      nodes[i] = trieInsert(tree, root, words[i], 0);
    }

    triePushDown(tree, root, -tree[root].children);

    std::vector<int> out(N);
    for (int i = 0; i < N; i++) {
      out[i] = tree[nodes[i]].children;
    }
    return out;
  }
};

int
main()
{
  return 0;
}
