#include <array>
#include <limits>
#include <vector>

class Solution
{
  static constexpr int MAXN = 29;

  using AT = std::array<std::pair<int, int>, MAXN * MAXN * MAXN>;
  static std::pair<int, int> solve(const int ROW, AT& dp, const int l, const int r, const int k)
  {

    if (l == r)
      return { 1, 1 };

    if (r < l)
      return solve(ROW, dp, r, l, k);

    const int key = k * ROW * ROW + l * ROW + r;
    if (dp[key] != std::pair<int, int>{ -1, -1 }) {
      return dp[key];
    }

    int earliest = std::numeric_limits<int>::max();
    int latest = 0;

    int maxPlayers = (k + 1) / 2;
    // we generate all possible positions.
    for (int i = 1; i <= l; i++) {
      for (int j = l - i + 1; j < (r - i + 1); j++) {
        if (maxPlayers < (i + j))
          continue;

        // I'm not totally sure what we are testing here.
        // They say it is to not jump over, but I really don't know.
        if ((i + j) < (l + r - k / 2))
          continue;

        auto [newEarliest, newLatest] = solve(ROW, dp, i, j, maxPlayers);
        earliest = std::min(earliest, 1 + newEarliest);
        latest = std::max(latest, 1 + newLatest);
      }
    }

    dp[key] = { earliest, latest };
    /*
    std::cout << "we are at: l=" << l << " and r=" << r << " and k=" << k
              << " with ans={" << dp[key].first << ", " << dp[key].second
              << "}\n";
              */
    return dp[key];
  }

public:
  static std::vector<int> earliestAndLatest(const int N, int firstPlayer, int secondPlayer)
  {

    const int ROW = N + 1;
    AT dp;
    std::fill_n(dp.begin(), ROW * ROW * ROW, std::pair<int, int>{ -1, -1 });
    auto [earliest, latest] = solve(ROW, dp, firstPlayer, N - secondPlayer + 1, N);

    return { earliest, latest };
  }
};
