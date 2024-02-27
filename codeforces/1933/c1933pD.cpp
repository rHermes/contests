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

	std::map<UT,UT> ans;
	for (UT i = 0; i < N; i++) {
		UT x = 0;
		std::cin >> x;
		ans[x]++;
	}

	// If the two first elements are not the same, we can always pick the first one
	if (ans.begin()->second == 1) {
		std::cout << "YES" << std::endl;
		return;
	} else {
		// Now we must search for one, that when it hits the first one, doesn't become zero.
		const UT modder = ans.begin()->first;

		for (const auto& [v, _] : ans) {
			if (v % modder != 0) {
				std::cout << "YES" << std::endl;
				return;
			}
		}
	}

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
