#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	std::cin >> N;

	std::vector<UT> counts(2);
	UT sum = 0;
	for (UT i = 0; i < N; i++) {
		UT x = 0;
		std::cin >> x;
		sum = (sum + x) % 3;
		UT y = x % 3;
		if (y != 0) {
			counts[y-1]++;
		}
	}

	if (sum == 0) {
		std::cout << 0 << std::endl;
		return;
	} else if (sum == 2) {
		std::cout << 1 << std::endl;
	} else if (sum == 1) {
		if (0 < counts[0]) {
			std::cout << 1 << std::endl;
		} else {
			std::cout << 2 << std::endl;
		}
	}
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
