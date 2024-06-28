#include <vector>

class Solution
{

public:
  static int numMusicPlaylists(int n, int goal, int k)
  {
    constexpr int MODN = 1000000007;

    // Y = playlist of length
    // X = unique songs used
    const int ROW = n + 1;
    std::vector<long> dp((goal + 1) * ROW, 0);
    dp[0 * ROW + 0] = 1;

    for (int i = 1; i <= goal; i++) {
      for (int j = 1; j <= std::min(i, n); j++) {
        // The ith song is a new song
        dp[i * ROW + j] = dp[(i - 1) * ROW + j - 1] * (n - j + 1) % MODN;

        // The i-th song is a song we have played before
        if (k < j) {
          dp[i * ROW + j] = (dp[i * ROW + j] + dp[(i - 1) * ROW + j] * (j - k)) % MODN;
        }
      }
    }

    return dp[goal * ROW + n];
  }
};
