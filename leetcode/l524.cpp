#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
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
    std::array<int, 26> children{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    bool end{ false };
  };
  std::vector<TrieNode> m_nodes;

public:
  [[nodiscard]] constexpr TrieNode& getNode(int idx) { return m_nodes[idx]; }
  [[nodiscard]] constexpr const TrieNode& getNode(int idx) const { return m_nodes[idx]; }

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

  [[nodiscard]] constexpr int next(const int curIdx, const char c) const
  {
    const auto& node = getNode(curIdx);

    const int cidx = c - 'a';
    const int nextId = node.children[cidx];
    return nextId;
  }
};

class Solution
{
public:
  static std::string findLongestWord(const std::string& s, const std::vector<std::string>& dictionary)
  {
    TrieForest forest;
    const auto root = forest.getFreshNode();

    for (const auto& word : dictionary) {
      forest.insert(root, word, 0);
    }

    // Ok, now we have all nodes.
    std::unordered_map<int, std::string> workingSet;
    workingSet.emplace(root, "");

    for (const auto c : s) {
      std::vector<std::pair<int, int>> nexts;
      for (const auto& [id, _] : workingSet) {
        const auto next = forest.next(id, c);
        if (next == -1) {
          continue;
        }
        if (auto it = workingSet.find(next); it == workingSet.end()) {
          nexts.emplace_back(id, next);
        }
      }

      for (const auto& [prev, next] : nexts) {
        workingSet.emplace(next, workingSet[prev] + c);
      }
    }

    std::string ans = "";
    for (const auto& [id, res] : workingSet) {
      if (res.size() < ans.size()) {
        continue;
      }

      if (res.size() == ans.size()) {
        if (ans <= res) {
          continue;
        }
      }

      if (forest.getNode(id).end) {
        ans = res;
      }
    }

    return ans;
  }
};
