#include <cstdio>
#include <cstdint>

#include <cmath>

using ST = std::int64_t;
using UT = std::uint64_t;

int main(void) {
	ST N, M;
	scanf("%ld %ld", &N, &M);
	/* solve(N, M); */

	const double DN = static_cast<double>(N);
	const double DM = static_cast<double>(M);

	const double q = 12*DM - 3*DN*DN;
	if (q < 0) {
		printf("no\n");
		return 0;
	}

	const double x = std::sqrt(q);
	const double ans = std::max(DN + x, DN - x);
	printf("%.7f\n", ans/4.0);


	return 0;
}
