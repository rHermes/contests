#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT M = 0;
	UT X = 0;
	std::cin >> N >> M >> X;

	std::set<UT> pos;
	pos.emplace(X-1);

	std::string lel;
	for (UT i = 0; i < M; i++) {
		UT dist = 0;
		std::set<UT> nextPos;

		std::cin >> dist >> lel;
		/* std::cout << dist << "[" << lel << "]" << std::endl; */
		if (lel[0] == '0') {
			for (const auto& p : pos) {
				nextPos.emplace((p+N+dist) % N);
			}
		}  else if (lel[0] == '1') {
			/* std::cout << "we are going against the current" << std::endl; */
			for (const auto& p : pos) {
				nextPos.emplace((p+N-dist) % N);
			}
		} else {
			for (const auto& p : pos) {
				nextPos.emplace((p+N+dist) % N);
				nextPos.emplace((p+N-dist) % N);
			}
		}

		pos = std::move(nextPos);
	}

	std::cout << pos.size() << std::endl;
	for (const auto& p : pos) {
		std::cout << p+1 << " ";
	}
	std::cout << std::endl;
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
