#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT a = 0;
	UT b = 0;
	UT l = 0;
	std::cin >> a >> b >> l;

	if (a < b)
		std::swap(a, b);

	/* // Check if they share the exact same prime numbers. */
	/* UT ka = a; */
	/* // B cannot be 1 */
	/* while ((ka % b == 0) && ka != b) */
	/* 	ka /= b; */

	/* if (ka == b) { */
	/* 	/1* std::cout << "We are going to have a wrong answer" << std::endl; *1/ */
	/* 	a = b; */
	/* 	b = 1; */
	/* } */


	// we want always to remove the biggest first
	std::set<UT> ks;
	for (UT ax = 1; (l % ax) == 0; ax *= a) {
		UT left = (l / ax);
		for (UT bx = 1; (left % bx) == 0; bx *= b) {
			ks.emplace(left / bx);
		}
	}
	
	/* std::cout << a << " " << b << " " << l << std::endl; */
	std::cout << ks.size() << std::endl;
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
