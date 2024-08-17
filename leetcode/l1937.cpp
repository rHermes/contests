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
  static constexpr long long maxPoints(const std::vector<std::vector<int>>& points)
  {
    const int ROWS = points.size();
    const int COLS = points[0].size();

    std::vector<long long> dp(COLS, 0);

    for (int row = 0; row < ROWS - 1; row++) {
      // We will now add these two together
      for (int i = 0; i < COLS; i++) {
        dp[i] += points[row][i];
      }

      // Now we spread these out, so we get the maximum for each position,
      // for the next row.
      for (int i = 1; i < COLS; i++) {
        dp[i] = std::max(dp[i], dp[i - 1] - 1);
      }

      for (int i = COLS - 2; 0 <= i; i--) {
        dp[i] = std::max(dp[i], dp[i + 1] - 1);
      }
    }

    long long ans = 0;

    for (int i = 0; i < COLS; i++) {
      ans = std::max(ans, dp[i] + points[ROWS - 1][i]);
    }

    return ans;
  }
};
