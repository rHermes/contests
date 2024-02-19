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
	UT N = 7;


	std::array<std::array<UT, 9>, 9> cover{};
	for (UT i = 0; i < 9; i++) {
		cover[i].fill(0);
	}

	for (UT i = 1; i <= N; i++) {
		std::string wow;
		std::getline(std::cin >> std::ws, wow);

		for (UT j = 1; j <= N; j++) {
			if (wow[j-1] == 'B') {
				/* val[i][j] = true; */
				cover[i][j]++;

				cover[i-1][j-1]++;
				cover[i-1][j+1]++;
				cover[i+1][j-1]++;
				cover[i+1][j+1]++;
			}
		}
	}


	// Find the positions we need to remove
	using P = std::pair<UT,UT>;
	std::map<P, std::set<P>> willRemove;

	for (UT i = 1; i <= N; i++) {
		for (UT j = 1; j <= N; j++) {
			if (cover[i][j] != 5)
				continue;

			willRemove[{i,j}].emplace(i, j);	
			willRemove[{i,j}].emplace(i-1,j-1);
			willRemove[{i,j}].emplace(i-1,j+1);
			willRemove[{i,j}].emplace(i+1,j-1);
			willRemove[{i,j}].emplace(i+1,j+1);
		}
	}


	/* UT ans = 0; */
	std::set<P> taken;
	while (!willRemove.empty()) {
		std::map<P, std::set<P>> count;

		for (const auto& [pos, removes] : willRemove) {
			for (const auto& can : removes) {
				if (!taken.count(can)) {
					count[can].insert(pos);
				}
			}
		}

		if (count.empty())
			break;

		/* ans++; */
		P maxC;
		UT maxCan = 0;
		for (const auto& [can, removes] : count) {
			if (maxCan < removes.size()) {
				maxCan = removes.size();
				maxC = can;
			}

			/* if (maxCan == 5) */
			/* 	break; */
		}
		
		taken.insert(maxC);
		for (const auto& rem : count[maxC]) {
			willRemove.erase(rem);
		}

		/* std::cout << "For this round we are removing (" << maxC.first << " , " << maxC.second << ")" << std::endl; */
	}

	std::cout << taken.size() << std::endl;

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
