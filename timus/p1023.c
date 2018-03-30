/*
 * p1023 - Buttons
 *
 * The answer is always the smallest divisor of the number larger
 * than 2, minus 1. I don't know why this is, but to solve it then,
 * we simply just calculate this number and then go to town.
 */
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#define TT uint_fast32_t
#define STT SCNuFAST32
#define PTT PRIuFAST32

int main() {
	TT K;
	scanf("%" STT, &K);

	if (K % 3 == 0) {
		printf("2\n");
		return 0;
	} else if (K % 4 == 0) {
		printf("3\n");
		return 0;
	}
	
	// Since 2 isn't a valid factor, we can eliminate if it is present
	// in the number.
	if (K % 2 == 0) {
		K /= 2;
	}

	TT LIM = ceil(sqrt(K)) + 1;
	for (TT L = 5; L <= LIM; L += 2) {
		if (K % L == 0) {
			printf("%" PTT "\n", L-1);
			return 0;
		}
	}

	printf("%" PTT "\n", K-1);

	return 0;
}
