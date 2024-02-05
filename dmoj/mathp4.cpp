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
	UT times = 0;
	while (true) {
		double mid = (hi + lo) / 2;
		double t = root_area(mid, c);

		if (std::abs(t) < tolerance) {
			/* printf("Times to get answer: %lu\n", times); */
			return mid;
		}

		if (t < 0)
			lo = mid;
		else
			hi = mid;

		times++;
	}
}

int main(void) {
	UT N;
	scanf("%lu", &N);

	for (UT i = 1; i < N; i++) {
		const double area_ratio = static_cast<double>(N-i)/N;
		const double angle = find_angle(area_ratio);
		const double height = std::cos(angle / 2);
		/* printf("We have angle: %lf and height: %.11f\n", angle, height); */
		printf("%.11f\n", height);
	}


	return 0;
}
