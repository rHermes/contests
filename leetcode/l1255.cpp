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
  using T = std::array<char, 26>;

  static int solve(const std::vector<std::pair<T, int>>& avail, const T& left, const int sumSoFar, const int idx)
  {
    if (idx == static_cast<int>(avail.size()))
      return sumSoFar;

    const auto& [wneed, wscore] = avail[idx];

    // The amount of datacopy is so small, we don't need to do any
    // addition or subtraction, we just copy it in and operate on it.
    T tmp = left;

    bool good = true;
    for (int i = 0; i < 26; i++) {
      tmp[i] -= wneed[i];
      if (tmp[i] < 0) {
        good = false;
        break;
      }
    }

    int ans = solve(avail, left, sumSoFar, idx + 1);
    if (good)
      ans = std::max(ans, solve(avail, tmp, sumSoFar + wscore, idx + 1));

    return ans;
  }

public:
  static int maxScoreWords(const std::vector<std::string>& words,
                           const std::vector<char>& letters,
                           const std::vector<int>& scores)
  {
    const int N = words.size();

    // we first convert each word into a score.
    std::vector<std::pair<T, int>> available(N);
    for (int i = 0; i < N; i++) {
      const auto& s = words[i];
      auto& [needed, points] = available[i];
      for (const auto c : s) {
        needed[c - 'a']++;
        points += scores[c - 'a'];
      }
    }

    // ok, now we accumulate our letters.
    T base{};
    for (const auto c : letters) {
      base[c - 'a']++;
    }

    return solve(available, base, 0, 0);
  }
};
