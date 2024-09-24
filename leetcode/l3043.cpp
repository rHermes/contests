#include <array>
#include <iostream>
#include <string_view>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class TrieForest
{
  struct TrieNode
  {
    std::array<int, 10> children{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
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

  constexpr void insert(const int curIdx, const std::string_view str)
  {
    if (str.empty())
      return;

    auto& node = getNode(curIdx);

    const int cidx = str.front() - '0';
    if (node.children[cidx] < 0) {
      auto newId = getFreshNode();
      getNode(curIdx).children[cidx] = newId;
      return insert(newId, str.substr(1));
    } else {
      return insert(node.children[cidx], str.substr(1));
    }
  }

  [[nodiscard]] constexpr int maxDepth(const int rootIdx, const std::string_view str) const
  {
    int curIdx = rootIdx;
    int ans = 0;
    for (const auto c : str) {
      const int idx = c - '0';
      curIdx = getNode(curIdx).children[idx];

      if (curIdx == -1)
        break;

      ans++;
    }
    return ans;
  }
};

class Solution
{
public:
  static int longestCommonPrefix(const std::vector<int>& arr1, const std::vector<int>& arr2)
  {

    TrieForest forest;
    const auto rootIdx = forest.getFreshNode();

    std::array<char, 10> buf;
    for (const auto x : arr1) {
      const auto [ptr, ec] = std::to_chars(buf.data(), buf.data() + buf.size(), x, 10);
      forest.insert(rootIdx, { buf.data(), ptr });
    }

    int ans = 0;

    for (const auto x : arr2) {
      const auto [ptr, ec] = std::to_chars(buf.data(), buf.data() + buf.size(), x, 10);

      const std::string_view num{ buf.data(), ptr };

      if (ans < static_cast<int>(num.size()) <= ans)
        ans = std::max(ans, forest.maxDepth(rootIdx, num));
    }

    return ans;
  }
};
