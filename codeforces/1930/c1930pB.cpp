#include <cstdio>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
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
		scanf(SCU, &N);

		// We just try this for now, just to check.
		std::vector<UT> ans(N);
		UT cur = 1;
		for (UT i = 0; i < N; i+=2) {
			ans[i] = cur;
			cur++;
		}
		for (UT i = 1; i < N; i+=2) {
			ans[i] = cur;
			cur++;
		}

		/* printf("WE are tryting For N = %lu this:\n", N); */
		for (auto x : ans)
			printf("%lu ", x);
		printf("\n");

		// Check it.
		/* for (UT i = 0; i < N-1; i++) { */
		/* 	for (UT j = 0; j < N-1; j++) { */
		/* 		if (j == i) */
		/* 			continue; */

		/* 		if ((ans[j] % ans[i] == 0) && (ans[j+1] % ans[i+1] == 0)) { */
		/* 			printf("This failed for N=%lu, and I=%lu and J=%lu\n", N, i, j); */
		/* 			break; */
		/* 		} */
		/* 	} */
		/* } */
	}

	return 0;
}
