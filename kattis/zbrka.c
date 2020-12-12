/*
 * The idea here is that in the sequence 1 got to be somewhere. So we can 
 * express the number of sequences with a certain confusion number as a
 * sum of sequences with the confusion number where 1 in a certain spot.
 *
 * We define f(n,c) as the number of sequences of length n, that have a
 * confusion number of c. We define g(n,c,i) as the number of sequences
 * of length n that has a confusion number of c and have 1 in the i-th
 * place, where i-th is zero indexed.
 *
 * for g(0,n,c) we have f(n-1,c), since 1 cannot be confused with any
 * number in the rest of the sequence. For g(1, n, c) we have f(n-1, c-1),
 * because no matter what number we choose, the first number will be
 * confused with 1. If we repeat this, we see a pattern:
 *
 * g(0,n,c) = f(n-1,c)
 * g(1,n,c) = (n-1,c-1)
 * g(2,n,c) = (n-1,c-2)
 * ...
 *
 * From this we see that the relationship is g(x,n,c) = f(n-1,c-x).
 * We can then form:
 *
 * f(n,c) = sum(g(x,n,c) for x in [0,n-1])
 *
 * which becomes
 *
 * f(n,c) = sum(f(n-1, c-x) for x in [0,n-1])
 *
 * This solution is however still O(N^2 * K) when implemented with
 * dynamic programming, which is still to slow. We need to realize
 *
 * f(n,c) = f(n, k-1) + f(n-1,k) - f(n-1, k-n)
 *
 * This leads to a O(N*K) solution, and we only need to keep track of
 * two arrays.
 *
 * I had to look at the solution to get the last part, I managed to get
 * the O(N^2 * K) solution. They don't explain how they arrived at the
 * relationship above, so I didn't really learn a lot from this exercise.
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#define MAX_C 10001
#define MOD 1000000007

#define UINT uint_fast32_t
#define UINT_SCN SCNuFAST32
#define UINT_PRI PRIuFAST32

int main(void) {
	UINT n, c;
	if(scanf("%"UINT_SCN "%"UINT_SCN, &n, &c) != 2) {
		perror("invalid input");
		return 1;
	}

	UINT dp[2][MAX_C];
	// We need to zero out the c+1 first elements of the array
	memset(&(dp[1]), 0, sizeof(UINT)*(c+1));

	// The only thing we know is that for a length of 1,
	// we can create 1 sequence with 0 confusion
	dp[1][0] = 1;
	

	for (UINT i = 2; i <= n; i++) {
		// Tmp is f(n, k-1)
		UINT tmp = 0;
		
		// So we loop through the Ks
		for (UINT j = 0; j <= c; j++) {
			// We switch between two arrays based on the 1 bit in the number.
			// This is tmp + f(n-1, k) which is the same as = f(n, k-1) + f(n-1, k)
			tmp = (tmp + dp[(i-1)&1][j]) % MOD;
			
			// if j isn't more or equal to i, it would be 0 anyway
			if (j >= i) {
				// The mod is ensure that this doesn't become negative, not sure if it is needed.
				tmp = (tmp - dp[(i-1)&1][j-i] + MOD) % MOD;
			}
			
			dp[i&1][j] = tmp;
		}
	}
	printf("%" UINT_PRI "\n", dp[n&1][c]);

	return 0;
}
