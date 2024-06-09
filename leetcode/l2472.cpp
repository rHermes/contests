#include <string>
#include <vector>

class Solution
{
  static bool isPalin(const std::string& s, int from, int to)
  {
    while (from < to) {
      if (s[from] != s[to])
        return false;

      from++;
      to--;
    }

    return true;
  }

public:
  static int maxPalindromes(const std::string& s, const int k)
  {
    const int N = s.size();

    std::vector<int> dp(N + 1, 0);
    for (int l = N - k; 0 <= l; l--) {
      dp[l] = dp[l + 1];
      // we only need to check 2 spots, because otherwise, a shorter
      // palindrome will exist to our right.
      for (int j = 0; j < 2; j++) {
        if (isPalin(s, l, l + k + j - 1)) {
          dp[l] = std::max(dp[l], 1 + dp[l + k + j]);
          break;
        }
      }
    }

    return dp[0];
  }
};
