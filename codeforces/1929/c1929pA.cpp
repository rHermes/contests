#include <cstdio>
#include <cinttypes>

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits>

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT T = 0;
	scanf("%lu", &T);

	for (UT i = 0; i < T; i++) {
		UT N = 0;
		scanf("%lu", &N);
		UT mmin = std::numeric_limits<UT>::max();
		UT mmax = 0;

		for (UT j = 0; j < N; j++) {
			UT x = 0;
			scanf("%lu", &x);

			mmin = std::min(mmin, x);
			mmax = std::max(mmax, x);
		}

		printf("%lu\n", mmax - mmin);
	}
	return 0;
}
