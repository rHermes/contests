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
	/* std::cout << "NEW TEST CASE\n\n\n\n" << std::endl; */
	UT N = 0;
	std::cin >> N;

	std::vector<UT> psa(N+1);
	for (UT i = 1; i <= N; i++) {
		std::cin >> psa[i];
		psa[i] += psa[i-1];
	}

	UT Q = 0;
	std::cin >> Q;

	for (UT q = 0; q < Q; q++) {
		UT L = 0;
		ST U = 0;
		std::cin >> L >> U;
		/* std::cout << "Evaluting: L=" << L << " U=" << U << std::endl; */

		auto eval = [=](ST x) { return x*U - ((x-1)*x)/2;};
		UT desired = psa[L-1] + static_cast<UT>(U);
		auto OUR_START = psa.begin() + static_cast<ST>(L);
		auto it = std::lower_bound(OUR_START, psa.end(), desired);

		if (it == psa.end()) {
			std::cout << N << " ";
		} else if (it == OUR_START) {
			std::cout << L << " ";
		}else if (*it == static_cast<UT>(desired)) {
			std::cout << std::distance(psa.begin(), it) << " ";
		} else {
			/* std::cout << "O3 "; */
			// it could be that this spot is closer. We need to check.
			UT cur = *it;
			UT prv = *(psa.begin() + std::distance(psa.begin(), it)-1);

			ST cur_val = eval(static_cast<ST>(cur - psa[L-1]));
			ST prv_val = eval(static_cast<ST>(prv - psa[L-1]));
			if (cur_val <= prv_val) {
				std::cout << std::distance(psa.begin(), it)-1 << " ";
			} else {
				std::cout << std::distance(psa.begin(), it) << " ";
			}
		}
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
		/* break; */
	}
}
