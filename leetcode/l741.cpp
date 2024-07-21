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

  static constexpr int solve(const std::vector<std::vector<int>>& grid,
                             const int N,
                             std::vector<int>& dp,
                             const int r1,
                             const int c1,
                             const int r2)
  {
    const int key = r1 * N * N + c1 * N + r2;
    if (dp[key] != -2) {
      return dp[key];
    }
    // We know that r1 + c1 = r2 + c2 <=> c2 = r1 + c1 - r2
    const int c2 = r1 + c1 - r2;

    if (grid[r1][c1] == -1 || grid[r2][c2] == -1) {
      dp[key] = -1;
      return -1;
    }

    const bool sameSpot = (r1 == r2) && (c1 == c2);

    int sum = grid[r1][c1];
    if (!sameSpot) {
      sum += grid[r2][c2];
    } else if (r1 == N - 1 && c1 == N - 1) {
      dp[key] = sum;
      return sum;
    }

    int ans = -1;
    if (r1 < N - 1) {
      if (r2 < N - 1) {
        ans = std::max(ans, solve(grid, N, dp, r1 + 1, c1, r2 + 1));
      }

      if (c2 < N - 1) {
        ans = std::max(ans, solve(grid, N, dp, r1 + 1, c1, r2));
      }
    }

    if (c1 < N - 1) {
      if (c1 < c2 && r2 < N - 1) {
        ans = std::max(ans, solve(grid, N, dp, r1, c1 + 1, r2 + 1));
      }

      if (c2 < N - 1) {
        ans = std::max(ans, solve(grid, N, dp, r1, c1 + 1, r2));
      }
    }

    if (ans != -1) {
      dp[key] = ans + sum;
    } else {
      dp[key] = -1;
    }
    return dp[key];
  }

public:
  static int cherryPickup(const std::vector<std::vector<int>>& grid)
  {
    const int N = grid.size();

    // -2 = unknown
    // -1 = known to not work
    // default = total value
    std::vector<int> dp(N * N * N, -2);

    return std::max(0, solve(grid, N, dp, 0, 0, 0));
  }
};
