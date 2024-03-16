#include <iostream>
#include <map>
#include <set>
/* #include <memory_resource> */
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <deque>

using UT = std::uint64_t;
using ST = std::int64_t;


void solve() {
	std::string line;
	std::cin >> line;

	const UT N = line.size();
	if (N == 1) {
		std::cout << 0 << std::endl;
		return;
	}

	// We try as big a length as we can. The clue here, is that we don't need to
	// start from the beginning for each time we fail. Each length is just a linear
	// search through the task, because if we fail at a position, it would have failed
	// all others behind it also. So we just start again.
	for (UT len = N/2; 0 < len; len--) {
		UT currentMatch = 0;
		for (UT i = 0; i + len < N; i++) {
			if (line[i] == line[i+len] || line[i] == '?' || line[i+len] == '?') {
				currentMatch++;
				if (currentMatch == len) {
					std::cout << 2 * len << std::endl;
					return;
				}
			} else {
				currentMatch = 0;
			}
		}
	}

	std::cout << 0 << std::endl;
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
