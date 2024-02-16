#include <cstdio>
#include <cstdint>

#include <array>
#include <numbers>
#include <cmath>
#include <unordered_map>
#include <vector>

using ST = std::int64_t;
using UT = std::uint64_t;

/*
 * https://www.youtube.com/watch?v=DBR6eW3MuiU
 * https://m00nlight.github.io/algorithm/2015/04/11/hackerrank-ncr
 * https://discuss.codechef.com/t/your-approach-to-solve-sandwich/14618/12
 * https://codeforces.com/blog/entry/10271
 * https://www.quora.com/What-are-some-good-implementations-of-the-general-Lucas%E2%80%99-theorem-in-C++
 * https://math.stackexchange.com/questions/95491/n-choose-k-bmod-m-using-chinese-remainder-theorem
 * https://github.com/plasmatic1/dmoj-solutions/blob/32555fe4df6e2dc862de55c1a52ea5da155166f7/cpp/mathp13.cpp#L4
 */


std::vector<std::pair<UT,UT>> trial_division1(UT n) {
	std::vector<std::pair<UT,UT>> fact;
	for (UT d = 2; d*d <= n; d++) {
		UT times = 0;
		while (n % d == 0) {
			times += 1;
			n /= d;
		}

		if (0 < times)
			fact.emplace_back(d, times);

	}

	if (1 < n)
		fact.emplace_back(n, 1);

	return fact;
}




int main(void) {
	UT N, K, M;
	scanf("%lu %lu %lu", &K, &N, &M);

	return 0;
}
