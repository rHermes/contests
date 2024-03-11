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
	std::vector<ST> a(N);

	for (UT i = 0; i < N; i++)
		std::cin >> a[i];

	// We must begin with the left one.
	for (UT i = 1; i < N-1; i++) {
		if (a[i] < 0) {
			std::cout << "NO" << std::endl;
			return;
		}

		// Ok, so how many times do we need to apply this operation.
		const auto timesNeeded = a[i-1];
		a[i-1] = 0;
		a[i] -= 2*timesNeeded;
		a[i+1] -= timesNeeded;

		if (a[i] < 0) {
			std::cout << "NO" << std::endl;
			return;
		}
	}

	if (a[N-1] == 0 && a[N-2] == 0)
		std::cout << "YES" << std::endl;
	else
		std::cout << "NO" << std::endl;

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
