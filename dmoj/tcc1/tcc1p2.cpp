#include <cstdio>
#include <array>
#include <cinttypes>
#include <vector>
/* #include <iostream> */

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT N = 0;
	UT K = 0;
	scanf("%lu %lu", &N, &K);

	std::vector<UT> AS(N+1);
	for (UT i = 1; i <= N; i++) {
		scanf("%lu", &AS[i]);
	}

	std::vector<UT> XS(K+1);
	for (UT i = 1; i <= K; i++)
		scanf("%lu", &XS[i]);

	std::vector<UT> ANS(K+1);
	std::vector<UT> SKIPS(K+1);

	for (UT i = N; 0 < i; i--) {
		const auto val = AS[i];

		// D
		SKIPS[val] += XS[val];

		// All others
		for (UT d = 1; d <= K; d++) {
			if (val == d)
				continue;

			if (SKIPS[d] == 0) {
				ANS[d] += val;
			} else {
				SKIPS[d]--;
			}
		}
	}

	for (UT k = 1; k <= K; k++) {
		printf("%lu\n", ANS[k]);
	}


	
	/*
	for (UT d = 1; d <= K; d++) {
		// These are the ranges we don't want.
		const auto xd = XS[d];
	
		// OK our plan is to keep the spans that are valid in the vector
		// and when they are erased, we simply respond to that.
		
		UT leftToSkip = 0;
		UT ans = 0;
		for (UT i = N; 0 < i; i--) {
			if (i <= leftToSkip) {
				break;
			}

			if (AS[i] != d) {
				if (leftToSkip == 0) {
					ans += AS[i];
				} else {
					leftToSkip--;
				}
			} else {
				leftToSkip += xd;
			}
		}

		printf("%lu\n", ans);
	}
*/
	return 0;
}
