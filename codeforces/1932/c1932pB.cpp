#include <string>
#include <cstdio>
#include <vector>
#include <cinttypes>

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
		scanf(SCU, &N);
		UT ans = 0;

		for (UT i = 0; i < N; i++) {
			UT cur = 0;
			scanf(SCU, &cur);

			UT nextInst = (ans / cur) + 1;
			ans = cur*nextInst;
		}
	
		printf(PRU "\n", ans);

	}
	return 0;
}
