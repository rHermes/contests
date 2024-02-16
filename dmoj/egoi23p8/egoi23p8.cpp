#include <cinttypes>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using UT = std::uint64_t;
using ST = std::int64_t;

/* constexpr UT MAX_N = 100000; */


void phase_one(const UT N) {
	const UT K = N - 1;
	std::cout << K << std::endl;

	for (UT i = 0; i < N-1; i++) {
		UT house_idx = 0;
		std::cin >> house_idx;

		std::cout << i + 1 << std::endl;
	}
}

void phase_two(const UT N) {
	
	std::vector<UT> houses(N);
	for (UT i = 0; i < N; i++) {
		std::cin >> houses[i];
	}

	std::unordered_map<UT,std::unordered_set<UT>> multiMap;
	for (UT i = 0; i < N; i++) {
		auto& hs = multiMap[houses[i]];
		hs.emplace(i);
		if (hs.size() == 2) {
			auto it = hs.begin();
			std::cout << *(it++) << " " << *it << std::endl;
			return;
		}
	}
}

int main() {
	std::cin.sync_with_stdio(0);
	std::cin.tie(0);

	UT P, N = 0;
	std::cin >> P >> N;

	if (P == 1) {
		phase_one(N);
	} else if (P == 2) {
		phase_two(N);
	}

	return 0;
}
