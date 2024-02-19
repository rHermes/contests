#include <iostream>
#include <cstdio>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <numeric>
#include <cinttypes>
#include <string>
#include <bitset>

using UT = std::uint32_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	std::cin >> N;
	
	UT ans = 0;
	std::multiset<UT> group;
	for (UT i = 0; i < N; i++) {
		UT x = 0;
		std::cin >> x;

		/* std::cout << std::bitset<32>(x) << std::endl; */

		UT y = (~x) ^ (1UL<<31);
		if (auto it = group.find(y); it != group.end()) {
			group.erase(it);
		} else {
			ans++;
			group.insert(x);
		}
	}
	std::cout << ans << std::endl;
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);
	std::cin.exceptions(std::cin.badbit);

	UT T = 0;
	std::cin >> T;
	for (UT t = 0; t < T; t++)
		solve();

	return 0;
}
