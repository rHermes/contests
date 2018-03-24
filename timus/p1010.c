/*
 * p1010 - Discrete Function
 *
 * There is one thing that is vital to understanding this is that we really
 * only need to check the numbers that are right next to each other. This
 * makes the problem trivial.
 */
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int main() {
	int32_t N;
	int64_t cur, prev;

	int64_t max_arc = 0;
	int32_t ret = 0;
	
	// First we get n.
	scanf("%" SCNd32, &N);

	// Then we get the first.
	scanf("%" SCNd64, &prev);
	
	for (int32_t i = 1; i < N-1; i++) {
		scanf("%" SCNd64, &cur);

		int64_t arc = llabs(cur - prev);
		// The first one is the only one we need to consider for negative.
		if (arc > max_arc) {
			max_arc = arc;
			ret = i;
		}

		prev = cur;
	}

	printf("%" PRId32 " %" PRId32 "\n", ret, ret + 1);

	return 0;
}

