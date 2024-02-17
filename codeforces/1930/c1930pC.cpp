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

		std::vector<UT> A(N);
		for (UT i = 0; i < N; i++)
			scanf(SCU, &A[i]);
	
		/*
		std::set<UT> ans;
		solveCase(A, ans);
		
		for (auto it = ans.rbegin(); it != ans.rend(); it++) {
			printf(PRU " ", *it);
		}

		printf("\n");
		*/
	}

	return 0;
}
