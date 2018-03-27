/*
 * p1820 - Ural Steaks
 *
 * Very simple problem, but it caught me by suprise that my intuition was
 * wrong at first. The key here is to realize that instead of frying steaks,
 * we are really frying sides. There are 2*N sides to fry and we can fry K
 * sides at a time. Answer is then ceil(2*N/K);
 *
 * I don't know how to make this faster, but it's still stuck at 0.015
 */
#include <stdio.h>
#include <inttypes.h>

int main() {
	uint16_t N, K;
	scanf("%" SCNu16 " %" SCNu16, &N, &K);
	// This is a trick to round up with integer division.
	printf("%" PRIu16 "\n", (N <= K) ? 2 : (2*N - 1)/K +1);
	return 0;
}
