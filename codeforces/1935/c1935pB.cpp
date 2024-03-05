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

	std::vector<UT> A(N);
	std::vector<bool> seen(N+1);
	for (UT i = 0; i < N; i++) {
		std::cin >> A[i];
		seen[A[i]] = true;
	}

	UT MEXWHOLE = 0;
	while (seen[MEXWHOLE])
		MEXWHOLE++;

	/* std::cout << "ThE WHOLE MEX " << MEXWHOLE << std::endl; */


	// we can always solve it in 2 ranges or not at all.
	UT split = 0;
	UT curMMEX = 0;

	seen = std::vector<bool>(N+1);
	/* std::cout << seen[0] << std::endl; */
	for (; split < N; split++) {
		seen[A[split]] = true;
		while (seen[curMMEX])
			curMMEX++;

		if (curMMEX == MEXWHOLE) {
			// We have our split.
			break;
		}
	}
	
	UT firstSplit = split;
	split++;
	
	UT secMMEX = 0;
	seen = std::vector<bool>(N+1);
	// Now the last.
	for (; split < N; split++) {
		seen[A[split]] = true;
		while (seen[secMMEX])
			secMMEX++;

		if (curMMEX < secMMEX)
			break; // early exit
	}

	if (N-2 < firstSplit || curMMEX != secMMEX) {
		std::cout << -1 << std::endl;
	} else {
		// N-1
		std::cout << 2 << std::endl;
		std::cout << 1 << " " << firstSplit+1 << std::endl;
		std::cout <<  firstSplit+2 << " " << N << std::endl;
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
