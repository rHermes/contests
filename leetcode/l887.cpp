#include <numeric>
#include <vector>
class Solution
{

  static int solve(std::vector<int>& memo, const int ROW, const int eggs, const int floors)
  {
    const int key = eggs * ROW + floors;
    if (memo[key] != -1)
      return memo[key];

    int lo = 1;
    int hi = floors;

    while (lo < hi) {
      const auto mid = std::midpoint(lo, hi + 1);

      int breakCount = solve(memo, ROW, eggs - 1, mid - 1);    // Egg breaks
      int noBreakCount = solve(memo, ROW, eggs, floors - mid); // Egg doesn't break.

      // We are looking to balance the break and the non break count.
      if (breakCount <= noBreakCount) {
        lo = mid;
      } else {
        hi = mid - 1;
      }
    }

    // Low is the critical floor, where the balance breaks.
    int ans = 1 + std::max(solve(memo, ROW, eggs - 1, lo - 1), solve(memo, ROW, eggs, floors - lo));
    memo[key] = ans;
    return ans;
  }

public:
  static int superEggDrop(const int k, const int n)
  {
    const int ROW = n + 1;

    // Y: number of eggs left
    // X: number of floors to cover
    std::vector<int> dp((k + 1) * ROW, -1);

    // Initialize the known values
    for (int floors = 1; floors <= n; floors++)
      dp[1 * ROW + floors] = floors;

    for (int eggs = 0; eggs <= k; eggs++)
      dp[eggs * ROW + 0] = 0;

    return solve(dp, ROW, k, n);
  }
};
