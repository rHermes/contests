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

	if (N % 2 != 0) {
		std::cout << "NO" << std::endl;
		return;
	}

	std::string sol;
	sol.reserve(N);
	if (N % 4 != 0) {
		sol += "CC";
	}
	for (auto i = sol.size(); i < N; i += 4) {
		sol += "AABB";
	}
	std::cout << "YES\n" << sol << std::endl;
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
