#include <iostream>
#include <cstdio>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <numeric>
#include <cinttypes>
#include <string>

using UT = std::uint64_t;
using ST = std::int64_t;

UT sumOfDigits(UT d) {
		UT digitSum = d % 10;
		UT curNum = d / 10;
		while (0 < curNum) {
			digitSum += curNum % 10;
			curNum /= 10;
		}

		return digitSum;
}

std::vector<UT> cache;
void solve() {
	UT N = 0;
	std::cin >> N;

	for (UT i = cache.size(); i <= N; i++) {
		cache.push_back(cache.back() + sumOfDigits(i));
	}

	std::cout << cache[N] << std::endl;
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);
	std::cin.exceptions(std::cin.badbit);

	// To make sure we don't waste time on reallocations
	cache.reserve(200001);
	cache.push_back(0);
	UT T = 0;
	std::cin >> T;
	for (UT t = 0; t < T; t++)
		solve();

	return 0;
}
