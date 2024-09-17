#include <array>
#include <limits>

class Solution
{
public:
  static constexpr int getMoneyAmount(const int N)
  {
    // There is no closed form solution on this it seems, not even a good
    // way to fix this.
    std::array<int, 200 * 200> dp;

    // Prefill the known answers for lengths 1-4

    for (int i = 0; i < N; i++) {
      dp[i * N + i] = 0;
    }

    // All of length two are easy, it's always the smaller one.
    for (int i = 0; i < N - 1; i++) {
      dp[i * N + (i + 1)] = i + 1;
    }

    // All of length three are easy too, it's just the middle one
    for (int i = 0; i < N - 2; i++) {
      dp[i * N + (i + 2)] = i + 2;
    }

    // All of length four are easy too, it's just a small adjustment.
    for (int i = 0; i < N - 3; i++) {
      dp[i * N + (i + 3)] = i + 1 + i + 3;
    }

    // Now we skip over to dynamic buildup
    for (int len = 4; len < N; len++) {
      // We know that we are always going to go upward?
      for (int start = 0; start < N - len; start++) {
        const int end = start + len;

        int minRes = std::numeric_limits<int>::max();

        // So we have a symmetry here, but it's never going to be more
        // profitable to be on the right side than the left side. That
        // is why we skip straight there.
        for (int piv = start + (len / 2); piv < end; piv++) {
          const int res = (piv + 1) + std::max(dp[start * N + piv - 1], dp[(piv + 1) * N + end]);
          minRes = std::min(minRes, res);
        }
        minRes = std::min(minRes, (end + 1) + dp[start * N + end - 1]);

        dp[(start)*N + (start + len)] = minRes;
      }
    }

    return dp[0 * N + N - 1];
  }
};
