#include <array>
#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

// This is setup, so we can also create one tree of each length, to search
// faster. I ended up not doing that here, as this actually ends up being just
// as fast, and we spend less memory. The thing that speeds a lot of stuff up
// here, is that we end up pooling the nodes, so both acquiring and release is
// easy. It also means we get better cache locality, except in certain
// pathalogical cases.
class TrieForest
{
  struct TrieNode
  {
    std::array<int, 26> children{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    int under{ 0 };
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

  constexpr void reserve(const int len) { m_nodes.reserve(len); }

  constexpr int insert(const int curIdx, const std::string& str, const int idx)
  {
    auto& node = getNode(curIdx);
    node.under++;

    if (idx == static_cast<int>(str.size())) {
      return curIdx;
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

  [[nodiscard]] constexpr int getUnder(const int curIdx) const { return getNode(curIdx).under; }

  constexpr void pushDown(const int curIdx, const int above)
  {
    auto& node = getNode(curIdx);

    node.under += above;

    for (int i = 0; i < 26; i++) {
      if (node.children[i] != -1) {
        pushDown(node.children[i], node.under);
      }
    }
  }
};

class Solution
{
public:
  static std::vector<int> sumPrefixScores(const std::vector<std::string>& words)
  {
    const int N = words.size();

    TrieForest forest;
    forest.reserve(10000);

    const auto root = forest.getFreshNode();

    std::vector<int> nodes(N);
    for (int i = 0; i < N; i++) {
      nodes[i] = forest.insert(root, words[i], 0);
    }

    // We are now going to reverse the tally, so it's not
    // how many you have below you, but rather how many you have above you.
    forest.pushDown(root, -forest.getUnder(root));

    std::vector<int> out(N);
    for (int i = 0; i < N; i++) {
      out[i] = forest.getUnder(nodes[i]);
    }
    return out;
  }
};
;
