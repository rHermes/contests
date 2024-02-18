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

		
		std::vector<std::pair<UT,UT>> ranges;
		for (UT i = 0; i < M; i++) {
			UT a = 0;
			UT b = 0;
			scanf(SCU, &a);
			scanf(SCU, &b);
			ranges.emplace_back(a,b);
		}

		std::sort(ranges.begin(), ranges.end());
		std::vector<UT> begin(M);
		std::vector<UT> end(M);
		for (UT i = 0; i < M; i++) {
			begin[i] = ranges[i].first;
			end[i] = ranges[i].second;
		}


		std::vector<UT> maxCats(M+1);
		for (ST i = static_cast<ST>(M-1); 0 <= i; i--) {
			UT j = static_cast<UT>(i);
			// The array we can pick from next, will be the first one, which is greater
			// than the current length
			auto nextIT = upper_bound(begin.begin() + i + 1, begin.end(), end[j]);
			auto dis = std::distance(begin.begin(), nextIT);
			/* UT nextIndex = static_cast<UT>(std::distance(begin.begin(), upper_bound(begin.begin() + i + 1, begin.end(), end[j]))); */
			/* printf("LOL %lu\n", nextIndex); */
			UT nextIndex = static_cast<UT>(dis);
			printf("The next index after %lu is %lu\n", i, nextIndex);
			maxCats[j] = std::max(maxCats[j + 1], maxCats[nextIndex] + end[j] - begin[j] + 1);
		}


	
		printf(PRU "\n", maxCats[0]);

	}
	return 0;
}
