#include <string>
#include <cstdio>
#include <vector>
#include <cinttypes>
#include <algorithm>

// Because codeforces has a different view of this.
#define SCU "%" SCNu64 " "
#define SCD "%" SCNd64 " "
#define PRU "%" PRIu64
#define PRD "%" PRId64

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT T = 0;
	scanf(SCU, &T);

	for (UT t = 0; t < T; t++) {
		UT N = 0;
		UT M = 0;
		scanf(SCU, &N);
		scanf(SCU, &M);

		
		std::vector<UT> nextRanges(N+1);
		std::vector<ST> catsInSpot(N+1);
		for (UT i = 0; i < M; i++) {
			UT a = 0;
			UT b = 0;
			scanf(SCU, &a);
			scanf(SCU, &b);

			a--;
			b--;
			catsInSpot[a] += 1;
			catsInSpot[b+1] -= 1;
			nextRanges[a] = std::max(nextRanges[a], b+1);
		}

		for (UT i = 0; i < N; i++)
			catsInSpot[i+1] += catsInSpot[i];

		for (UT i = 0; i < N; i++)
			nextRanges[i+1] = std::max(nextRanges[i+1], nextRanges[i]);

		std::vector<ST> maxCats(N+1);
		for (UT i = N; 0 < i; i--) {
			const UT idx = i-1;
			maxCats[idx] = std::max(maxCats[idx+1], catsInSpot[idx] + maxCats[nextRanges[idx]]);
		}
	
		printf(PRU "\n", maxCats[0]);

	}
	return 0;
}
