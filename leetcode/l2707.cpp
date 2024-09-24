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
  using CACHE = std::vector<int>;

  static int solve(CACHE& cache,
                   const int SN,
                   const TrieNode& root,
                   const std::string_view& s,
                   const int L,
                   const int R)
  {
    if (R < L) {
      return 0;
    }

    // ok, so let's get the key
    const int key = L * SN + R;
    if (cache[key] != -1) {
      return cache[key];
    }

    // this is the max answer of course.
    int ans = R - L + 1;

    for (int l = L; l <= R; l++) {
      // ok, we are going to be iterating now.
      TrieNode const* cur = &root;

      int r = l;
      while (r <= R) {
        const int idx = s[r] - 'a';
        cur = cur->children[idx].get();
        if (!cur)
          break;

        if (cur->found) {
          // ok, so we can split here.
          const int pre = solve(cache, SN, root, s, L, l - 1);
          const int post = solve(cache, SN, root, s, r + 1, R);
          ans = std::min(ans, pre + post);
        }

        r++;
      }
    }

    cache[key] = ans;
    return ans;
  }

public:
  static int minExtraChar(const std::string& s, const std::vector<std::string>& dictionary)
  {
    TrieNode root;

    for (const auto& word : dictionary) {
      root.insert(word);
    }

    const int SN = s.size();
    std::vector<int> cache(SN * SN, -1);

    return solve(cache, SN, root, s, 0, SN - 1);
  }
};
