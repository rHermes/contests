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
  static int solve(const std::vector<std::vector<int>>& grid, int ROWS, int COLS, std::vector<int>& dp, int y, int x)
  {
    int key = y * COLS + x;
    if (dp[key] != -1)
      return dp[key];

    int ans = 1;
    const int me = grid[y][x];

    if (0 < y && me < grid[y - 1][x])
      ans = std::max(ans, 1 + solve(grid, ROWS, COLS, dp, y - 1, x));

    if (0 < x && me < grid[y][x - 1])
      ans = std::max(ans, 1 + solve(grid, ROWS, COLS, dp, y, x - 1));

    if (y < ROWS - 1 && me < grid[y + 1][x])
      ans = std::max(ans, 1 + solve(grid, ROWS, COLS, dp, y + 1, x));

    if (x < COLS - 1 && me < grid[y][x + 1])
      ans = std::max(ans, 1 + solve(grid, ROWS, COLS, dp, y, x + 1));

    dp[key] = ans;
    return ans;
  }

public:
  static int longestIncreasingPath(const std::vector<std::vector<int>>& matrix)
  {
    // This is actually very nice. Since it has to be increasing
    // Ok, so we can actually just cache this one.

    const int ROWS = matrix.size();
    const int COLS = matrix[0].size();
    std::vector<int> dp(ROWS * COLS, -1);

    int ans = 0;
    for (int y = 0; y < ROWS; y++) {
      for (int x = 0; x < COLS; x++) {
        ans = std::max(ans, solve(matrix, ROWS, COLS, dp, y, x));
      }
    }
    return ans;
  }
};
