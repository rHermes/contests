#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

struct TrieNode
{
  bool found{ false };
  std::array<std::unique_ptr<TrieNode>, 26> children{};

  void insert(const std::string_view sv)
  {
    if (sv.empty()) {
      found = true;
      return;
    }

    const auto idx = sv.front() - 'a';
    if (!children[idx])
      children[idx] = std::make_unique<TrieNode>();

    children[idx]->insert(sv.substr(1));
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
  static int minExtraChar(const std::string& s, const std::vector<std::string>& dictionary)
  {
    TrieNode root;

    for (const auto& word : dictionary) {
      root.insert(word);
    }

    const int SN = s.size();
    std::array<int, 51> dp;
    std::ranges::fill_n(dp.begin() + 1, 50, std::numeric_limits<int>::max());
    dp[0] = 0;

    for (int l = 0; l < SN; l++) {
      // We always make sure to init the one in front of us.
      dp[l + 1] = std::min(dp[l + 1], dp[l] + 1);

      // we will now follow the trie. We could do more here maybe?
      TrieNode const* cur = &root;
      for (int r = l; r < SN; r++) {
        const auto idx = s[r] - 'a';
        cur = cur->children[idx].get();

        if (!cur) {
          break;
        }

        if (cur->found) {
          // ok, so now we have a new oppertunity
          dp[r + 1] = std::min(dp[r + 1], dp[l]);
        }
      }
    }

    return dp[SN];
  }
};
