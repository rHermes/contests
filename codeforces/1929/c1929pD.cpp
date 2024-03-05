#include <cstdio>
#include <cinttypes>

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <cmath>

using UT = std::uint64_t;
using ST = std::int64_t;

constexpr UT MOD_M = 998244353;


UT solveDP(const std::vector<std::vector<UT>>& G, std::vector<UT>& DP, const UT prev, const UT cur) {
	UT ans = 1;
	for (const auto& next : G[cur]) {
		if (next == prev)
			continue;

		ans = (ans * (solveDP(G, DP, cur, next) + 1)) % MOD_M;
	}

	DP[cur] = ans % MOD_M;
	return DP[cur];
}

int main() {
	UT T = 0;
	scanf("%" SCNu64, &T);

	for (UT t = 0; t < T; t++) {
		UT N = 0;
		scanf("%" SCNu64, &N);

		std::vector<std::vector<UT>> G(N);
		for (UT i = 0; i < N-1; i++) {
			UT a = 0;
			UT b = 0;
			scanf("%" SCNu64 " %" SCNu64, &a, &b);

			G[a-1].push_back(b-1);
			G[b-1].push_back(a-1);
		}

		// We always root the tree in 0, this is just to make our lives easier.	
		std::vector<UT> dp(N);
		solveDP(G, dp, 0, 0);

		UT ans = 1;
		for (UT i = 0; i < N; i++)
			ans = (ans + dp[i]) % MOD_M;

		printf("%" PRIu64 "\n", ans);
	}
	return 0;
}
