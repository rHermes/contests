#include <cstdint>
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
  static int numberOfPaths(const std::vector<std::vector<int>>& grid, const int k)
  {
    // So it's a DFS over k.
    const int ROWS = grid.size();
    const int COLS = grid[0].size();

    std::vector<int> dp(ROWS * COLS * k, 0);
    using T = std::int64_t;

    constexpr T MODN = 1000000007;

    const auto pindex = [=](const int row, const int col, const int sm) {
      return (row * COLS * k) + col * k + (sm % k);
    };

    // The first square.
    dp[pindex(0, 0, grid[0][0])] = 1;

    // The top
    for (int col = 1; col < COLS; col++) {
      for (int kz = 0; kz < k; kz++) {
        dp[pindex(0, col, grid[0][col] + kz)] = dp[pindex(0, col - 1, kz)];
      }
    }

    // The left margin
    for (int row = 1; row < ROWS; row++) {
      for (int kz = 0; kz < k; kz++) {
        dp[pindex(row, 0, grid[row][0] + kz)] = dp[pindex(row - 1, 0, kz)];
      }
    }

    // The rest of the board
    for (int row = 1; row < ROWS; row++) {
      for (int col = 1; col < COLS; col++) {
        for (int kz = 0; kz < k; kz++) {
          dp[pindex(row, col, grid[row][col] + kz)] =
            (dp[pindex(row, col - 1, kz)] + dp[pindex(row - 1, col, kz)]) % MODN;
        }
      }
    }

    return dp[pindex(ROWS - 1, COLS - 1, 0)];
  }
};
