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
	
	std::vector<UT> hits(N);
	for (UT i = 0; i < N; i++) {
		UT x = 0;
		std::cin >> x;
		hits[x]++;
	}

	/* for (const auto& p: hits) { */
	/* 	std::cout << p << " "; */
	/* } */
	/* std::cout << std::endl; */

	
	bool seenOne = false;
	for (UT i = 0; i < N; i++) {
		if (hits[i] == 0) {
			std::cout << i << std::endl;
			return;
		} if (hits[i] == 1) {
			if (seenOne) {
				std::cout << i << std::endl;
				return;
			} else {
				seenOne = true;
			}
		}
	}
	std::cout << N << std::endl;
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
