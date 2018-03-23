/*
 * p1014 - Product of Digits
 *
 * This is actually rather simple. If you prime
 * factor the number you have all the things needed.
 * We don't really need to do this here, as we can simply
 * go through the one we have.
 */

#include <stdio.h>
#include <inttypes.h>

int main() {
	uint32_t N;
	scanf("%" SCNu32, &N);
	
	// Q have to be a positive integer.
	if (N == 0) {
		printf("10\n");
		return 0;
	} else if (N == 1) {
		printf("1\n");
		return 0;
	}

	uint64_t Q = 0;
	uint64_t place = 1;
	
	// We simply remove each digits as many times as we can.
	for (int i = 9; i > 1 && N != 1; i--) {
		while (N % i == 0) {
			N /= i;
			Q += i*place;
			place *= 10;
		}
	}

	if (N != 1) {
		printf("-1\n");
	} else {
		printf("%" PRIu64 "\n", Q);
	}

	return 0;
}
