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

		std::vector<UT> nums(2*N);
		for (UT i = 0; i < 2*N; i++) {
			scanf(SCU, &nums[i]);
		}

		std::sort(nums.begin(), nums.end());

		UT ans = 0;
		for (UT i = 0; i < 2*N; i += 2) {
			ans += nums[i];
		}

		printf(PRU "\n", ans);
	}

	return 0;
}
