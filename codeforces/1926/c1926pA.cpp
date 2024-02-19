#include <iostream>
#include <cstdio>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <numeric>
#include <cinttypes>
#include <string>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT A = 0;
	UT B = 0;

	std::string wow;
	std::getline(std::cin >> std::ws, wow);

	/* std::cout << wow << std::endl; */
	for (auto it = wow.begin(); it != wow.end(); it++) {
		if (*it == 'A')
			A++;
		else if (*it == 'B')
			B++;
	}

	if (A < B)
		std::cout << 'B' << std::endl;
	else
		std::cout << 'A' << std::endl;
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
