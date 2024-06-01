#include <array>

class Solution
{
  static constexpr int MODN = 1000000007;
  static constexpr int MAXN = 201;

  static int solve(std::array<int, MAXN * MAXN * 2>& dp, const int N, int zero, int one, bool last, int limit)
  {
    const int key = zero * (N * 2) + one * 2 + last;
    if (dp[key] != -1)
      return dp[key];

    int ans = 0;

    if (last) {
      for (int i = 1; i <= std::min(limit, one); i++) {
        ans = (ans + solve(dp, N, zero, one - i, false, limit)) % MODN;
      }
    } else {
      for (int i = 1; i <= std::min(limit, zero); i++) {
        ans = (ans + solve(dp, N, zero - i, one, true, limit)) % MODN;
      }
    }

    dp[key] = ans;
    return ans;
  }

public:
  static int numberOfStableArrays(int zero, int one, int limit)
  {
    const int N = std::max(zero, one) + 1;
    std::array<int, MAXN * MAXN * 2> dp;
    std::fill_n(dp.begin(), N * N * 2, -1);

    dp[0 * N * 2 + 0 * 2 + 0] = 1;
    dp[0 * N * 2 + 0 * 2 + 1] = 1;

    int a = solve(dp, N, zero, one, true, limit);
    int b = solve(dp, N, zero, one, false, limit);
    return (a + b) % MODN;
  }
};

int
main()
{
  return 0;
}
