#include <cstdio>
#include <cstdint>
#include <vector>

using ST = std::int64_t;
using UT = std::uint64_t;

UT solve(std::vector<UT>& arr, ST L, ST R) {
	if (L == R)
		return 0;

	// We check to see if there is a number in the right
	// place which has all to the right of it.

	// We remove the edges:
	if (arr[L] == L)
		return solve(arr, L+1, R);

	if (arr[R] == R)
		return solve(arr, L, R-1);


	UT maxOnLeft = arr[L];
	for (UT i = L+1; i < R; i++) {
		const auto x = arr[i];
		if (x == i && (maxOnLeft+1) == x) {
			return solve(arr, L, i-1) + solve(arr, i+1, R);
		}

		maxOnLeft = std::max(maxOnLeft, x);
	}

	// If we arrive here, there will be no answer, so we return the number of swaps
	return R - L + 1;
}

int main() {
	UT N = 0;
	scanf("%lu", &N);
	
	// early exit
	if (N == 1) {
		printf("0\n");
		return 0;
	}

	std::vector<UT> arr;
	for (UT i = 0; i < N; i++) {
		UT x = 0;
		scanf("%lu", &x);
		arr.push_back(x-1);
	}


	auto ans = solve(arr, 0, N-1);
	printf("%lu\n", ans);


	return 0;
}
