/* #include <cstdio> */
#include <array>
#include <cinttypes>
#include <vector>
#include <iostream>

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT N = 0;
	std::cin >> N;
	/* scanf("%lu", &N); */
	std::vector<bool> voted(N);

	std::cin >> std::ws;
	std::string line;
	std::getline(std::cin, line);

	UT votedYes = 0;
	std::vector<UT> prefixSum(N+1);
	for (UT i = 0; i < N; i++) {
		if (line[i] == 'Y') {
			voted[i] = true;
			votedYes++;
			prefixSum[i+1] = prefixSum[i] + 1;
		} else if (line[i] == 'N') {
			voted[i] = false;
			prefixSum[i+1] = prefixSum[i];
		} else {
			throw std::exception();
		}
	}

	if (N < votedYes*2) {
		std::cout << "YES" << std::endl;
		return 0;
	}

	// The only parts we can change is part 1, the half of the array. We can
	// never change more than total votedYes.
	const UT halfWay = N/2 + 1;

	/* std::cout << "halfway: " << halfWay << std::endl; */
	/* std::cout << "halfway pa: " << prefixSum[halfWay-1] << std::endl; */


	// We need one Y over the halfway point, and we got it.
	bool hasOverHalfWay = prefixSum[N] > prefixSum[halfWay-1];
	if (hasOverHalfWay)
		std::cout << "YES" << std::endl;
	else
		std::cout << "NO" << std::endl;

	






	
	return 0;
}
