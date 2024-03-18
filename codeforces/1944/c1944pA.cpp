#include <iostream>
#include <cstdint>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT K = 0;
	std::cin >> N >> K;

	if (K < N-1) {
		std::cout << N << '\n';
	} else {
		std::cout << 1 << '\n';
	}
}

int main() {
	std::cin.tie(nullptr);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
