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
public:
  static int minCut(const std::string& s)
  {

    const int N = s.size();
    std::vector<int> dp(N + 1);
    dp[0] = -1;

    std::vector<unsigned char> cache(N * N, false);

    for (int r = 0; r < N; r++) {
      int minCuts = r;

      for (int l = 0; l <= r; l++) {
        if (s[l] != s[r]) {
          continue;
        }

        // if we should check the cache at all or not.
        if (1 < r - l && !cache[(r - 1) * N + l + 1])
          continue;

        cache[r * N + l] = true;
        minCuts = std::min(minCuts, 1 + dp[l]);
      }

      dp[r + 1] = minCuts;
    }

    return dp.back();
  }
};

int
main()
{
  return 0;
}
