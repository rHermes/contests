#include <iostream>
#include <limits>
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
  static int cherryPickup(const std::vector<std::vector<int>>& grid)
  {
    // We can simply run the experiment twice here.
    const int ROWS = grid.size();
    const int COLS = grid.front().size();

    // Just two of them to swap back and forth.
    std::vector<int> dp(COLS * COLS, -std::numeric_limits<int>::max());
    std::vector<int> prevDP(COLS * COLS, 0);

    dp[0 + COLS - 1] = grid[0].front() + grid[0].back();

    int ans = -std::numeric_limits<int>::max();

    for (int row = 1; row < ROWS; row++) {
      std::swap(dp, prevDP);
      // we do the first and last ones uniquly.

      for (int curL = 0; curL < COLS; curL++) {
        // so we now have (A ==B)
        // meaning we can have. (A-1, B), (A-1, B+1), (A, B+1)
        int maxHere = prevDP[curL * COLS + curL];
        if (0 < curL && curL < COLS - 1)
          maxHere = std::max(maxHere, prevDP[(curL - 1) * COLS + curL + 1]);

        if (0 < curL)
          maxHere = std::max(maxHere, prevDP[(curL - 1) * COLS + curL]);

        if (curL < COLS - 1)
          maxHere = std::max(maxHere, prevDP[(curL * COLS + curL + 1)]);

        dp[curL * COLS + curL] = maxHere + grid[row][curL];
        ans = std::max(ans, dp[curL * COLS + curL]);

        for (int curR = curL + 1; curR < COLS; curR++) {
          int maxi = -std::numeric_limits<int>::max();

          for (int ld = curL - 1; ld < curL + 2; ld++) {
            for (int rd = curR - 1; rd < curR + 2; rd++) {
              if (0 <= ld && ld <= rd && rd < COLS) {
                maxi = std::max(maxi, prevDP[ld * COLS + rd]);
              }
            }
          }
          dp[curL * COLS + curR] = grid[row][curL] + grid[row][curR] + maxi;
          ans = std::max(ans, dp[curL * COLS + curR]);
        }
      }
    }

    return ans;
  }
};
