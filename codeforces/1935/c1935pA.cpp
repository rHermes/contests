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

	std::string w;
	std::getline(std::cin >> std::ws, w);

	std::string lk(w.rbegin(), w.rend());

	std::string wow = w + lk;
	std::string wew = lk + w;

	std::string least = wow;
	if (std::lexicographical_compare(wew.begin(), wew.end(), least.begin(), least.end()))
		least = wew;

	// We have 3 choices here. Either reverse the string or add a new one.
	// All other operations are not needed.
	if (N % 2 != 0) {
		if (std::lexicographical_compare(lk.begin(), lk.end(), least.begin(), least.end())) {
			std::cout << lk << std::endl;
		} else {
			std::cout << least << std::endl;
		}
	} else {
		if (std::lexicographical_compare(w.begin(), w.end(), least.begin(), least.end())) {
			std::cout << w << std::endl;
		} else {
			std::cout << least << std::endl;
		}
	}
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
