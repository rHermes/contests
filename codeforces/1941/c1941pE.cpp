#include <iostream>
#include <map>
#include <limits>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT M = 0;
	UT K = 0;
	UT D = 0;
	std::cin >> N >> M >> K >> D;

	std::vector<UT> row(M);
	std::vector<UT> dp(M);
	std::vector<UT> bridgeCosts(N);

	for (UT i = 0; i < N; i++) {
		for (UT j = 0; j < M; j++) {
			std::cin >> row[j];
		}

		// We have scanned in the row now.
		// Ok, so I want to reduce the amount of cases, to make this easier on my brain.
		//
		// We always have supports at 0 and M-1
		if (M-1 <= D+1) {
			// We won't need any struts.
			bridgeCosts[i] = row[0] + row[M-1] + 1 + 1;
			continue;
		}

		// Ok, so we cannot reach all the way from the end to the start.
		// We will begin with the end.
		dp[M-1] = row[M-1]+1;
		
		// OK, so we know that for all which M-1 <= x + D + 1, the answer is just the row
		// plus the end.
		// M-1-D-1
		for (UT i = M-1-D-1; i < M-1; i++) {
			dp[i] = row[i]+1 + dp[M-1];
		}

		// Ok now our upper limit is M-1-D-1
		UT upperLimit = M-1-D-1;
		// But we also have a lower limit:
		for (UT i = upperLimit; 0 < i; i--) {
			UT ii = i-1;
			UT best = dp[ii+1];
			// we pick out the smallest of the next x.
			for (UT j = 2; j <= D+1; j++) {
				best = std::min(best, dp[ii+j]);
			}
			dp[ii] = row[ii]+1+best;
		}

		// ok, now dp[0], the almighty.
		bridgeCosts[i] = dp[0];
	}

	/* std::cout << "BRIDGE COSTS" << std::endl; */
	/* for (const auto& p : bridgeCosts) { */
	/* 	std::cout << p << std::endl; */
	/* } */
	/* std::cout << "END IT " << std::endl; */
	
	UT ans = std::numeric_limits<UT>::max();
	for (UT i = 0; i <= N-K; i++) {
		UT thisAns = 0;
		for (UT j = 0; j < K; j++) {
			thisAns += bridgeCosts[i+j];
		}

		ans = std::min(thisAns, ans);
	}


	std::cout << ans << std::endl;
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
