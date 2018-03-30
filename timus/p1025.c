/*
 * p1025 - Democracy in Danger
 *
 * Sort the groups by number of people and calculate what is needed for 
 * K/2 + 1 of those groups. We do the division as we read them in, since
 * we then can do a partial sum.
 *
 * We don't actually have to do any sorting either, we can simply record
 * how many there are of each, and then iterate through that.
 */

#include <stdio.h>
#include <inttypes.h>

#define TT uint_fast16_t

// this is how many people we are going to need.
// we only need half of the 9999 space, since we are going to be doing A / 2 +1
uint_fast8_t groups[5001] = {0};

int main() {
	uint_fast16_t K;
	scanf("%" SCNuFAST16, &K);
	
	for (uint_fast16_t i = 0; i < K; i++) {
		uint_fast16_t r;
		scanf("%" SCNuFAST16, &r);
		groups[r/2 + 1]++;
	}

	// Now we just loop through the values.
	uint_fast8_t groups_needed = K/2 + 1;
	uint_fast16_t answer = 0;
	for (uint_fast16_t i = 1; i < 5001; i++) {
		uint_fast16_t r = groups[i];
		if (r) {
			uint_fast16_t leka = (r > groups_needed) ? groups_needed : r;

			answer += leka * i;
			groups_needed -= leka;
		}

		if (groups_needed == 0) {
			break;
		}
	}

	printf("%" PRIuFAST16 "\n", answer);
	return 0;
}
