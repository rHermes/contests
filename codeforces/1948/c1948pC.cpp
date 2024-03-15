#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <array>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	std::cin >> N;

	std::array<std::string, 2> arr;
	std::cin >> arr[0] >> arr[1];

	/* std::cout << "[" << arr[0] << "]" << std::endl; */
	/* std::cout << "[" << arr[1] << "]" << std::endl; */

	std::set<std::pair<UT,UT>> seen;
	std::vector<std::pair<UT,UT>> Q;
	// y, x
	Q.emplace_back(0,0);
	while (!Q.empty()) {
		auto [cy, cx] = Q.back();
		Q.pop_back();

		if (auto it = seen.emplace(cy, cx); !it.second) {
			continue;
		}

		if (cy == 1 && cx == N-1) {
			std::cout << "YES" << std::endl;
			return;
		}

		const UT dy = (cy == 1) ? 0 : 1;
		if (arr[dy][cx] == '>') {
			Q.emplace_back(dy, cx+1);
		} else {
			Q.emplace_back(dy, cx-1);
		}

		if (0 < cx) {
			if (arr[cy][cx-1] == '<') {
				Q.emplace_back(cy, cx-2);
			}
		}

		if (cx < N-1) {
			if (arr[cy][cx+1] == '>') {
				Q.emplace_back(cy, cx+2);
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
