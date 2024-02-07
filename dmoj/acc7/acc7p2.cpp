/**
* acc7p2 - Code Review
*
* This is a cheeky task. I had to read the editorial for this one
* and the solution is simply that we try random permutations, as
* for larger values of N, we are unlikely to get a missmatch
* for many tries.
*
* I really don't like this, as it's a bit cheaty for me, but
* I respect the new angle.
*/

#include <cstdio>
#include <cstdint>
#include <vector>
#include <random>
#include <algorithm>

using UT = std::uint32_t;
using ST = std::int32_t;

int main() {
	UT N = 0;
	scanf("%u", &N);
	std::vector<UT> numbers(N);
	for (UT i = 0; i < N; i++) {
		numbers[i] = i+1;
	}

	std::mt19937 g;

	for (UT i = 0; i < 21; i++) {
		std::shuffle(numbers.begin(), numbers.end(), g);

		for (UT j = 0; j < N; j++) {
			if (j == N-1)
				printf("%u\n", numbers[j]);
			else
				printf("%u ", numbers[j]);
		}

		fflush(stdout);

		ST x = -1;
		scanf("%d", &x);
		if (x == 0 || x == -1) {
			break;
		}
	}

	return 0;
}
