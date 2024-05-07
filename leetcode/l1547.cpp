#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>

class Solution
{
public:
  int minCost(int n, std::vector<int>& cuts)
  {
    std::sort(cuts.begin(), cuts.end());

    // We are virtually adding 0 in the front and n in the back.
    const auto N = cuts.size() + 2;

    // and we are going to store it in one block, for better locality
    std::vector<std::int32_t> dp(N * N, 0);

    // dp[l][r] == best possible solution when cut starts at cuts[l] and ends at cuts[r].
    for (std::size_t L = N - 2; 0 < L; L--) {
      const auto LL    = L - 1;
      const auto LLcut = (LL == 0) ? 0 : cuts[LL - 1];

      for (std::size_t RR = LL + 2; RR < N; RR++) {
	auto ans = std::numeric_limits<std::int32_t>::max();

	for (std::size_t PL = LL + 1; PL < RR; PL++) {
	  ans = std::min(ans, dp[LL * N + PL] + dp[PL * N + RR]);
	}

	const auto RRcut = (RR == N - 1) ? n : cuts[RR - 1];
	dp[LL * N + RR]  = ans + (RRcut - LLcut);
      }
    }

    // Then we just return [0,N-1]
    return dp[0 * N + N - 1];
  }
};

int
main()
{
  return 0;
}
