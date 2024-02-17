#include <cstdio>
#include <cstdint>
#include <vector>
#include <unordered_set>
#include <map>
#include <cmath>
#include <queue>

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT N = 0;
	UT S = 0;
	UT T = 0;
	scanf("%lu %lu %lu\n", &N, &S, &T);

	std::vector<UT> powers(N);
	
	UT totalSum = 0;
	for (UT i = 0; i < N; i++) {
		scanf("%lu", &powers[i]);
		totalSum += powers[i];
	}

	if (N <= S*T) {
		printf("%lu\n", totalSum);
		return 0;
	}

	// We build a sumTable, so it's easier to test.
	std::vector<UT> sumTable(N+1);
	for (UT i = 0; i < N; i++) {
		sumTable[i+1] = sumTable[i] + powers[i];
	}
	
	UT maxScore = 0;
	for (UT left = 0; left <= T; left++) {
		// X left and X right
		UT l = S*left;
		UT r = N - S*(T-left);

		UT ans = totalSum - (sumTable[r-1+1] - sumTable[l-1+1]);
		maxScore = std::max(maxScore, ans);
	}

	printf("%lu\n", maxScore);

	return 0;
}
