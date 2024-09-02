#include <array>
#include <iostream>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

// This is setup, so we can also create one tree of each length, to search faster.
// I ended up not doing that here, as this actually ends up being just as fast, and
// we spend less memory. The thing that speeds a lot of stuff up here, is that
// we end up pooling the nodes, so both acquiring and release is easy. It also means
// we get better cache locality, except in certain pathalogical cases.
class TrieForest
{
  struct TrieNode
  {
    std::array<int, 26> children{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    bool end{ false };
  };
  std::vector<TrieNode> m_nodes;

  [[nodiscard]] constexpr TrieNode& getNode(int idx) { return m_nodes[idx]; }
  [[nodiscard]] constexpr const TrieNode& getNode(int idx) const { return m_nodes[idx]; }

public:
  [[nodiscard]] constexpr int getFreshNode()
  {
    int id = m_nodes.size();
    m_nodes.emplace_back();
    return id;
  }

  constexpr void insert(const int curIdx, const std::string& str, const int idx)
  {
    auto& node = getNode(curIdx);

    if (idx == static_cast<int>(str.size())) {
      node.end = true;
      return;
    }

    const int cidx = str[idx] - 'a';
    if (node.children[cidx] < 0) {
      auto newId = getFreshNode();
      getNode(curIdx).children[cidx] = newId;
      return insert(newId, str, idx + 1);
    } else {
      return insert(node.children[cidx], str, idx + 1);
    }
  }

  [[nodiscard]] constexpr bool query(const int curIdx, const std::string& str, const int idx) const
  {
    const auto& node = getNode(curIdx);

    if (idx == static_cast<int>(str.size())) {
      return node.end;
    }

    if (str[idx] == '.') {
      for (int i = 0; i < 26; i++) {
        const int nextId = node.children[i];
        if ((0 <= nextId) && query(nextId, str, idx + 1))
          return true;
      }
      return false;
    } else {
      const int cidx = str[idx] - 'a';
      const int nextId = node.children[cidx];
      return (0 <= nextId) && query(nextId, str, idx + 1);
    }
  }
};

class WordDictionary
{
  TrieForest m_forest;
  int m_root{ m_forest.getFreshNode() };

public:
  constexpr void addWord(const std::string& word) { m_forest.insert(m_root, word, 0); }
  constexpr bool search(const std::string& word) { return m_forest.query(m_root, word, 0); }
};
