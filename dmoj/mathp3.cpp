#include <cstdio>
#include <cstdint>

#include <array>
#include <set>

using ST = std::int64_t;
using UT = std::uint64_t;


constexpr UT MAX_N = 2 * 10 * 10 * 10 * 10 * 10 + 5;
std::array<UT, MAX_N> arr;
std::array<bool, MAX_N> less_than;
std::array<bool, MAX_N> taken;
std::array<UT, MAX_N> output;

int main(void) {
	UT N;
	scanf("%lu", &N);

	for (UT i = 0; i < N; i++) {
		scanf("%lu", &arr[i]);
	}
	arr[N] = arr[N-1];

	if (arr[0] != 1) {
		printf("-1\n");
		return 0;
	}

	std::set<UT> spots;

	for (UT i = 0; i < N; i++) {
		if (arr[i] != arr[i+1] && arr[i]+1 != arr[i+1]) {
			printf("-1\n");
			return 0;
		}

		if (arr[i] < arr[i+1])
			less_than[i] = true;

		spots.insert(i);

		/* if (less_than[i]) */
		/* 	printf("< "); */
		/* else */
		/* 	printf("> "); */
	}
	/* printf("\n"); */





	// We now check if it is possible.
	for (UT i = 1; i <= N; i++) {
		/* printf("We are staring on i=%lu\n", i); */
		for (auto it = spots.cbegin(); it != spots.cend(); it++) {
			const UT j = *it;
			if (j == 0) {
				// We can take if we are larger than taken or smaller than non taken
				bool right = 
						(taken[j+1] && !less_than[j]) // Larger than taken
						|| (!taken[j+1] && less_than[j]); // Smaller than non taken
				if (right) {
					output[j] = i;
					taken[j] = true;
					spots.erase(it);
					break;
				}
			}
			else if (j == N-1) {
				bool left = 
						(taken[j-1] && less_than[j-1]) // Larger than taken
						|| (!taken[j-1] && !less_than[j-1]); // Smaller than non taken
			
				if (left) {
					output[j] = i;
					taken[j] = true;
					spots.erase(it);
					break;
				}
			} else {
				bool right = 
						(taken[j+1] && !less_than[j]) // Larger than taken
						|| (!taken[j+1] && less_than[j]); // Smaller than non taken
				bool left = 
						(taken[j-1] && less_than[j-1]) // Larger than taken
						|| (!taken[j-1] && !less_than[j-1]); // Smaller than non taken

				if (left && right) {
					output[j] = i;
					taken[j] = true;
					spots.erase(it);
					break;
				}
			}
		}
	}
	
	// Print out the result
	for (UT i = 0; i < N; i++) {
		printf("%lu ", output[i]);
	}
	printf("\n");
	
	
	return 0;
}
