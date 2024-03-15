#include <iostream>
#include <map>
#include <set>
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
	/* std::cout << "[" << line << "]" << std::endl; */
	
	if (line.size() == 1) {
		std::cout << 0 << std::endl;
		return;
	}

	std::set<std::pair<std::size_t,std::size_t>> seen;
	std::deque<std::pair<std::size_t, std::size_t>> Q;


	if (line.size() % 2 == 0) {
		Q.emplace_back(0, line.size()-1);
	} else {
		Q.emplace_back(1, line.size()-1);
		Q.emplace_back(0, line.size()-2);
	}

	while (!Q.empty()) {
		auto [l, r] = Q.front();
		Q.pop_front();

		if (auto it = seen.emplace(l, r); !it.second)
			continue;


		// ok, we include r
		bool good = true;
		const UT ITS = (r-l+1)/2;
		/* std::cout << "Considering: [" << l << ", " << r << "] with ITS=" << ITS << ": " << line.substr(l, r-l+1) << std::endl; */
		for (UT i = 0; i < ITS; i++) {
			/* std::cout << "Comparing: " << line[l+i] << " and " << line[l+ITS+i] << std::endl; */
			if (line[l+i] != line[l+ITS+i] && (line[l+i] != '?') && (line[l+ITS+i] != '?')) {
				good = false;
				break;
			}
		}

		if (good) {
			std::cout << r-l+1 << std::endl;
			return;
		}

		if (l+1 < r) {
			Q.emplace_back(l+2, r);
			Q.emplace_back(l+1, r-1);
			Q.emplace_back(l, r-2);
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
		/* break; */
	}
}
