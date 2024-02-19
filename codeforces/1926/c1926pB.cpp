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
	UT N = 0;
	std::cin >> N;
	
	UT i = 0;
	std::string firstLine;
	for (; i < N; i++) {
		std::getline(std::cin >> std::ws, firstLine);
		if (firstLine.find('1') != firstLine.npos)
			break;
	}

	std::string secondLine;
	std::getline(std::cin >> std::ws, secondLine);

	if (firstLine == secondLine) {
		std::cout << "SQUARE" << std::endl;
	} else {
		std::cout << "TRIANGLE" << std::endl;
	}

	/* std::cout << "[" << firstLine << "] and [" << secondLine << "]" << std::endl; */
	i += 2 ;
	for (; i < N; i++)
		std::getline(std::cin >> std::ws, secondLine);
	

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
