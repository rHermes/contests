/*
 * p1024 - Permutations
 *
 * Here we use the fact that there will always be loops in these.
 * Each of these loops has a certain interval and then we just find the lcm 
 * of these.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#define MAXN 1000

#define TT uint_fast32_t
#define SCNT "%" SCNuFAST32
#define PRIT "%" PRIuFAST32

// This is used in order to keep track of the numbers.
TT inp[MAXN];

TT gcd(TT a, TT b) {
	while (b != 0) {
		TT t = b;
		b = a % b;
		a = t;
	}
	return a;
}

TT lcm(TT a, TT b) {
	if (a == 0 && b == 0) {
		return 0;
	}
	TT k = gcd(a, b);
	return (a/k) * b;
}

int main() {
	TT N;
	scanf(SCNT, &N);
	
	// Read in number.
	for (TT i = 0; i < N; i++) {
		scanf(SCNT, inp + i);
	}

	TT ans = 1;
	// Find the cycles.
	for (TT i = 0; i < N; i++) {
		// We must have visisted this before.
		if (inp[i] == 0) {
			continue;
		}

		// ok follow along this road, until we are back where we started.
		TT num = 1;
		TT k = inp[i];
		while (k-1 != i) {
			TT tmp = inp[k-1];
			inp[k-1] = 0;
			num++;
			k = tmp;
		}

		ans = lcm(ans, num);
	}

	printf(PRIT "\n", ans);

	return 0;
}
