#include <iostream>
#include <string>
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
    bool terminal{ false };
    std::array<int, 27> children{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
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

  constexpr void insert(const int curIdx, const std::string& str, const int N, const int idx)
  {
    auto& node = getNode(curIdx);

    if (idx == N) {
      node.terminal = true;
      return;
    }

    // ok, so we only care about if it's '/'.
    // if we have this, then we are just going to return.
    const int cidx = (str[idx] != '/') ? (str[idx] - 'a') : 26;

    /* This is to optimze the access. It breaks early. */
    if (str[idx] == '/' && node.terminal) {
      return;
    }

    if (node.children[cidx] < 0) {
      auto newId = getFreshNode();
      getNode(curIdx).children[cidx] = newId;
      insert(newId, str, N, idx + 1);
    } else {
      insert(node.children[cidx], str, N, idx + 1);
    }
  }

  constexpr void walkIt(const int curIdx, std::vector<std::string>& out, std::string& curPath) const
  {
    const auto& node = getNode(curIdx);

    if (node.terminal) {
      out.push_back(curPath);
    } else {
      if (node.children[26] != -1) {
        curPath.push_back('/');
        walkIt(node.children[26], out, curPath);
        curPath.pop_back();
      }
    }

    for (int i = 0; i < 26; i++) {
      if (node.children[i] != -1) {
        curPath.push_back('a' + i);
        walkIt(node.children[i], out, curPath);
        curPath.pop_back();
      }
    }
  }
};

class Solution
{
public:
  static std::vector<std::string> removeSubfolders(const std::vector<std::string>& folder)
  {
    const int N = folder.size();

    TrieForest forest;
    forest.reserve(10000);

    const auto root = forest.getFreshNode();

    for (const auto& ss : folder) {
      forest.insert(root, ss, ss.size(), 1);
    }

    // Ok, now we are going to walk through that graph.
    std::vector<std::string> out;
    out.reserve(N);
    std::string tmp = "/";

    forest.walkIt(root, out, tmp);

    return out;
  }
};
