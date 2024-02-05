#include <cstdio>
#include <cstdint>

#include <array>
#include <numbers>
#include <cmath>

using ST = std::int64_t;
using UT = std::uint64_t;

/* constexpr UT MAX_N = 1000; */
/* constexpr double TOL = 0.0000000000001; */
int main(void) {
	UT N;
	scanf("%lu", &N);
	UT ans = 0;

	UT u = static_cast<UT>(std::floor(std::sqrt(N)));
	for (UT k = 1; k <= u; k++) {
		ans += N/k;
	}

	ans *= 2;
	ans -= u*u;

	printf("%lu\n", ans);


	return 0;
}
