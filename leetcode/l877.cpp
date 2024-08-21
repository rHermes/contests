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
public:
  static constexpr bool stoneGame(const std::vector<int>& piles)
  {
    const int N = piles.size();

    // Store the maximum amount of stones the first player
    // will get total.
    const int ROW = N;
    std::vector<int> dp(N * ROW, -1);
    for (int i = 0; i < N; i++) {
      dp[i * ROW + i] = piles[i];
    }

    // ok, let's try this now then.
    for (int dist = 1; dist <= N; dist++) {
      for (int i = 0; i < N - dist; i++) {
        dp[i * ROW + i + dist] = std::max(dp[i * ROW + i] - dp[(i + 1) * ROW + i + dist],
                                          dp[(i + dist) * ROW + (i + dist)] - dp[i * ROW + i + dist - 1]);
      }
    }

    return 0 < dp[0 * ROW + N - 1];
  }
};
