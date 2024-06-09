#include <array>
#include <bitset>
#include <memory>
#include <string>
#include <vector>

constexpr int MAX_WORD_SIZE = 10;

class Trie
{
private:
  using HX = std::bitset<MAX_WORD_SIZE>;

  struct Node
  {
    std::array<std::unique_ptr<Node>, 26> children{};
    bool is_end{ false };

    void insert(std::string_view str)
    {
      if (str.empty()) {
        is_end = true;
        return;
      }

      const auto c = str.front() - 'a';
      str.remove_prefix(1);

      if (!children[c])
        children[c] = std::make_unique<Node>();

      children[c]->insert(str);
    }

    void hits(HX& indices, int depth, std::string_view str)
    {
      if (is_end) {
        indices[depth] = true;
      }

      if (str.empty()) {
        return;
      }

      const auto c = str.front() - 'a';
      str.remove_prefix(1);

      if (children[c]) {
        children[c]->hits(indices, depth + 1, str);
      }
    }
  };

  Node root{};

public:
  void insert(std::string_view str) { root.insert(str); }

  HX hits(std::string_view str)
  {
    HX indices{};
    root.hits(indices, -1, str);
    return indices;
  }
};

class Solution
{

  static void createOutput(std::vector<std::string>& out,
                           const std::string& s,
                           const std::vector<std::vector<int>>& jumps,
                           std::string& curStr,
                           const int idx)
  {
    if (idx == static_cast<int>(s.size())) {
      out.emplace_back(curStr);
      return;
    }

    for (const auto nextIdx : jumps[idx]) {
      const auto prevSize = curStr.size();
      if (idx != 0) {
        curStr += " " + s.substr(idx, nextIdx - idx);
        createOutput(out, s, jumps, curStr, nextIdx);
      } else {
        curStr += s.substr(idx, nextIdx - idx);
        createOutput(out, s, jumps, curStr, nextIdx);
      }
      curStr.resize(prevSize);
    }
  }

public:
  static std::vector<std::string> wordBreak(const std::string& s, const std::vector<std::string>& wordDict)
  {
    const int N = s.size();

    Trie trie;
    for (const auto& v : wordDict) {
      trie.insert(v);
    }

    // We store forward jumps and if anything has seen the position.
    // we could do this pure strings instead, but this ends up saving space
    // for long strings, where storing all the strings for all the previous
    // incantations would be long.
    std::vector<std::vector<int>> dp(N);
    std::vector<bool> seen(N);
    seen[0] = true;

    std::string_view view = s;
    for (int i = 0; i < N; i++, view.remove_prefix(1)) {
      // ok, so we are going to just figure out which
      if (!seen[i]) {
        continue;
      }

      auto hits = trie.hits(view);
      for (int j = 0; j < MAX_WORD_SIZE; j++) {
        if (!hits[j])
          continue;

        int sz = j + 1;
        dp[i].emplace_back(i + sz);
        seen[i + sz] = true;
      }
    }

    std::vector<std::string> out;
    std::string buffer;
    createOutput(out, s, dp, buffer, 0);
    return out;
  }
};
