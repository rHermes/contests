/**
 * This is taken from this comment. Even if I am aboard with the general idea, 
 * I am not totaly clear on all the points. I will revisit this tommorrow.
 * https://codeforces.com/blog/entry/125840?#comment-1118399
 */
#include <cstdio>
#include <vector>
#include <cinttypes>
#include <algorithm>

// Because codeforces has a different view of this.
#define SCU "%" SCNu64 " "
#define PRU "%" PRIu64

using UT = std::uint64_t;

int main() {
	UT T = 0;
	scanf(SCU, &T);
	for (UT t = 0; t < T; t++) {
		UT N = 0;
		scanf(SCU, &N);

		std::vector<UT> A(N);
		for (UT i = 0; i < N; i++) {
			scanf(SCU, &A[i]);
			A[i] += i+1;
		}

		std::sort(A.begin(), A.end(), std::greater<>());

		UT lastQ = 100000000000000;
		for (UT i = 0; i < N; i++) {
				lastQ = std::min(lastQ - 1, A[i]);
				printf(PRU " ", lastQ);
		}
		printf("\n");
	}

	return 0;
}
