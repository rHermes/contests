#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static constexpr int solve(std::vector<int>& dp, const std::string& cur, const int N, const int l, const int r)
  {
    if (r < l) {
      return 0;
    }

    const int key = N * l + r;
    if (dp[key] != -1) {
      return dp[key];
    }

    // Worst case, print each character individually.
    int ans = 1 + solve(dp, cur, N, l + 1, r);

    for (int k = l + 1; k <= r; k++) {
      // If we match the start and the end, then we go.
      if (cur[l] == cur[k]) {
        // Ok, so with this match, we can think of it like we take both
        // l and k in one move. In this case, that will be the same as
        // just ignoring k.
        int splitSolve = solve(dp, cur, N, l, k - 1) + solve(dp, cur, N, k + 1, r);
        ans = std::min(ans, splitSolve);
      }
    }

    dp[key] = ans;
    return ans;
  }

public:
  static constexpr int strangePrinter(std::string& s)
  {
    auto rng = std::ranges::unique(s);
    const int N = std::distance(s.begin(), rng.begin());

    std::vector<int> dp(N * N, -1);
    return solve(dp, s, N, 0, N - 1);
  }
};
