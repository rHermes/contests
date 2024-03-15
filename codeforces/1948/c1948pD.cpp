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

bool canWork(const std::string& line, const std::size_t N) {
	// THis returns if there are any ways to make this work inside the array.
	if (line.size() < N) {
		return false;
	}
	const UT ITS = N/2;

	for (UT l = 0; l < line.size()-N+1; l++) {
		bool good = true;
		/* std::cout << "Considering: [" << l << ", " << r << "] with ITS=" << ITS << ": " << line.substr(l, r-l+1) << std::endl; */
		for (UT i = 0; i < ITS; i++) {
			/* std::cout << "Comparing: " << line[l+i] << " and " << line[l+ITS+i] << std::endl; */
			if (line[l+i] != line[l+ITS+i] && (line[l+i] != '?') && (line[l+ITS+i] != '?')) {
				good = false;
				break;
			}
		}

		if (good) {
			return true;
		}
	}
	return false;
}

void solve() {
	std::string line;
	std::cin >> line;
	/* std::cout << "[" << line << "]" << std::endl; */
	
	if (line.size() == 1) {
		std::cout << 0 << std::endl;
		return;
	}
	
	UT i = line.size();
	if (line.size() % 2 != 0) {
		i--;
	}

	for (; 0 < i; i -= 2) {
		if (canWork(line, i)) {
			std::cout << i << std::endl;
			return;
		}
	}

	std::cout << 0 << std::endl;
	return;


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
