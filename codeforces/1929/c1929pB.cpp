#include <cstdio>
#include <cinttypes>

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <cmath>

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT T = 0;
	scanf("%lu", &T);

	for (UT i = 0; i < T; i++) {
		UT N = 0;
		UT K = 0;
		scanf("%lu %lu", &N, &K);
		
		UT ans = 0;
		if ((N + N-2)*2 <= K) {
			ans += N+N-2;
			K -= (N+N-2)*2;

			ans += K;
		} else {
			ans = K / 2 + (K % 2);
			/* ans = static_cast<UT>(std::ceil(static_cast<double>(K)/2.0)); */
		}
		printf("%lu\n", ans);
	}
	return 0;
}
