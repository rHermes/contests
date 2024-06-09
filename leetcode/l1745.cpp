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
  static bool checkPartitioning(const std::string& s)
  {
    const int N = s.size();
    std::vector<unsigned char> dp((N + 1) * 4, false);
    dp[0 + 0] = true;
    std::vector<unsigned char> cache(N * N, false);

    for (int r = 0; r < N; r++) {
      // we just need to check if it's true.
      for (int l = 0; l <= r; l++) {
        if (s[l] != s[r]) {
          continue;
        }

        // if we should check the cache at all or not.
        if (1 < r - l && !cache[(r - 1) * N + l + 1])
          continue;

        cache[r * N + l] = true;

        for (int i = 1; i < 4; i++) {
          dp[(r + 1) * 4 + i] |= dp[(l) * 4 + i - 1];
        }
      }
    }

    return dp[(N) * 4 + 3];
  }
};
