#include <cstdio>
#include <cstdint>

#include <array>
#include <numbers>
#include <cmath>

using ST = std::int64_t;
using UT = std::uint64_t;

inline double root_area(double x, double c) {
	return (x - std::sin(x)) - c;
}

double find_angle(const double area_ratio) {
	const double c = 2*std::numbers::pi * area_ratio;
	// We do a binary search for c;
	double hi = 8;
	double lo = -8;
	const double tolerance = 0.00000000001;

	while (true) {
		double mid = (hi + lo) / 2;
		double t = root_area(mid, c);

		if (std::abs(t) < tolerance) {
			return mid;
		}

		if (t < 0)
			lo = mid;
		else
			hi = mid;
	}
}

int main(void) {
	UT N;
	scanf("%lu", &N);

	// we can optimize this further, by only doing this half N times.
	for (UT i = 1; i < N; i++) {
		const double area_ratio = static_cast<double>(N-i)/N;
		const double angle = find_angle(area_ratio);
		const double height = std::cos(angle / 2);
		printf("%.11f\n", height);
	}


	return 0;
}
