/*
 *  p. 1009 - K-based Numbers
 *
 * I think this can be done recursively, with a function call like:
 *
 * possible(prev_zero, K, left)
 *
 * and then we can just cache that. The first call will just be:
 * possible(true, K, N)
 *
 * Even better, the formula for this is: ans[n] = (ans[n-1] + ans[n-2]) * (K-1)
 *
 * The reason for this is the fact that the first character can only be (K-1)
 * things, since it cant be 0. ans[n-1] is obvious, because for each of the
 * prefixes, we can have that many variations, and finally we add ans[n-2],
 * because ans[n-1] doesn't contain the possibility of a 0 prefix.
 */

#include <stdio.h>
#include <stdint.h>

// This is because my machine uses slightly different scanners than the
// online judge.
#ifdef ONLINE_JUDGE
#define LONG_SCAN "%llu"
#else
#define LONG_SCAN "%lu"
#endif

#define TT uint_fast64_t

int main() {
	TT N, K;

	scanf(LONG_SCAN "\n" LONG_SCAN, &N,&K);

	// we set and b2 to K-1.
	// We therfor start at N = 2;
	TT b2 = 1;
	TT b1 = K-1;
	for (TT i = 1; i < N; i++) {
		TT tmp = (b1 + b2) * (K-1);
		b2 = b1;
		b1 = tmp;
	}


	printf(LONG_SCAN "\n", b1);
	return 0;
}
