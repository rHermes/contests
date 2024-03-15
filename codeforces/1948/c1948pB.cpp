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

	std::vector<UT> arr(N);
	for (UT i = 0; i < N; i++)
		std::cin >> arr[i];

	// We can only split the array once.
	UT mm = 0;
	for (UT i = 0; i < N; i++) {
		// If the number can be safely extracted, we always want to do it.
		UT pr = arr[i];
		if (pr < mm) {
			std::cout << "NO" << std::endl;
			return;
		}
		
		if (pr < 10) {
			mm = pr;
			continue;
		}

		const UT front = pr/10;
		const UT back = pr%10;

		if (front <= back && mm <= front) {
			mm = back;
		} else {
			mm = pr;
		}
	}

	std::cout << "YES" << std::endl;
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
