// Holes problem.
//
//
// This can be done with dynamic programming. We just keep track of where we
// are going to end up on each step.
//
// It could not be done like this. It worked for a lot of the problems, but for
// frequent updates in the lower parts of the problem, we get a lot of updates.
// Instead we divide the problem area and then do some more computing, but avoid
// a lot of updates.
//
// There was some edge cases with my version, so this one is heavily inspired by
// http://codeforces.com/contest/13/submission/16644108

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define T int32_t

int main() {
	// First read in the answer.
	T N, M, K;
	int rc = scanf("%d %d", &N, &M);
	if (rc != 2) {
		printf("ONLY GOT ONE!\n");
		return -1;
	}

	// We calculate K.
	K = 0;
	while ((K+1)*(K+1) <= N) {
		K++;
	}


	// we keep 4 arrays.
	T *power = malloc((N+1)*sizeof(T));
	T *next = malloc((N+1)*sizeof(T));
	T *count = malloc((N+1)*sizeof(T));
	T *block = malloc((N+1)*sizeof(T));
	if (power == NULL || next == NULL || count == NULL || block == NULL) {
		printf("MALLOC FAILURE\n");
		return -1;
	}

	// Now we loop through the initial values.
	for (T i = 1; i <= N; i++) {
		if (scanf("%d", power + i) != 1) {
			printf("ERROR READING IN!\n");
			return -1;
		}
		block[i] = i/K;
	}
	
	// Initial setting of the values.
	for (T i = N; i >= 1; i--) {
		// If this would bring us down, we simply set 0
		if (i + power[i] > N) {
			next[i] = 0;
			count[i] = 1;
		} else if (!next[i + power[i]] || block[i + power[i]] > block[i]) {
			// If a jump brings us into the next block.
			next[i] = i + power[i];
			count[i] = 1;
		} else {
			// If a jump just brings us back to the same block.
			next[i] = next[i + power[i]];
			count[i] = count[i + power[i]] + 1;
		}
	}

	// Now we loop through the moves
	int des = 0, a = 0, b = 0;
	while (M--) {
		if (scanf("%d %d", &des, &a) != 2) {
			printf("ERROR READING IN!\n");
			return -1;
		}

		if (des == 0) {
			if(scanf("%d", &b) != 1) {
				printf("ERROR READING IN!\n");
				return -1;
			}
			power[a] = b;

			for (T i = a; i >= a - a%K; i--) {
				// If this would bring us down, we simply set 0
				if (i + power[i] > N) {
					next[i] = 0;
					count[i] = 1;
				} else if (!next[i + power[i]] || block[i + power[i]] > block[i]) {
					// If a jump brings us into the next block.
					next[i] = i + power[i];
					count[i] = 1;
				} else {
					// If a jump just brings us back to the same block.
					next[i] = next[i + power[i]];
					count[i] = count[i + power[i]] + 1;
				}
			}
		} else {
			// Sum up the counts as we go, and stop when we get to one with 0
			T sum = 0;
			for (; a; b = a, sum += count[a], a = next[a]);
			printf("%d %d\n", b, sum);
		}
	} 
	// we must free the holes info.
	free(power);
	free(next);
	free(count);
	free(block);

	return 0;
}
