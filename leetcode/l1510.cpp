#include <vector>

class Solution
{
public:
  static constexpr bool winnerSquareGame(const int N)
  {
    std::vector<char> dp(N + 1, false);

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j * j <= i; j++) {
        if (!dp[i - (j * j)]) {
          dp[i] = true;
          break;
        }
      }
    }

    return dp[N];
  }
};
