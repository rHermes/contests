/** 
* hhpc1p4 - HHPC1 P4 - Yet Another A+B Problem
*
* This turns out to be a rather interesting case. We define
* 1 <= c < a <= b
*
* 1/a + 1/b == 1/c
* (b + a) / a*b == 1/c
* c == a*b/(b+a)
*
* we expand:
*
* c * (a+b) == a*b
* c*a + c*b == a*b
* 0 == a*b - c*a - c*b
*
* We then use Simon's Favorite Factoring Trick[0],
* to get:
*
* 0 == a*(b - c) - c*b
* c^2 == a*(b - c) - c*b + c^2
* c^2 == a*(b - c) - c(b - c)
* c^2 == (a - c)*(b - c)
*
* Now as we are free to choose any a and b we want, it is easy to
* see that we can make (a - c) and (b - c) any integers we want.
*
* This means that we are really asking ourselves:
*
* What two integers x and y can be multiplied to produce c^2.
*
* This is just the divisor function for c^2.
*
*
* [0]: https://artofproblemsolving.com/wiki/index.php/Simon%27s_Favorite_Factoring_Trick
*/

#include <cstdint>
#include <cstdio>
#include <vector>

using UT = std::uint64_t;

std::vector<std::pair<UT,UT>> factor(UT x) {
	std::vector<std::pair<UT,UT>> facs;
	UT num2 = 0;
	while (x % 2 == 0) {
		num2++;
		x /= 2;
	}
	if (0 < num2)
			facs.emplace_back(2, num2);

	for (UT d = 3; d * d <= x; d += 2) {
		UT times = 0;
		while (x % d == 0) {
			times++;
			x /= d;
		}

		if (0 < times)
			facs.emplace_back(d, times);
	}

	if (1 < x) {
		facs.emplace_back(x, 1);
	}

	return facs;
}

UT solve(UT c) {
	// We primefactor c
	auto facs = factor(c);

	UT ans = 1;
	for (const auto& [_, times] : facs) {
		ans *= (2*times + 1);
	}

	return ans;
}

int main() {
	UT T = 0;
	scanf("%lu", &T);

	for (UT i = 0; i < T; i++) {
		UT c = 0;
		scanf("%lu", &c);
		printf("%lu\n", solve(c));
	}

	return 0;
}

