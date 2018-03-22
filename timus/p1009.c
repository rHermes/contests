/*
 *  p1009 - K-based Numbers
 *
 *  If you tinker with the equation for a bit, you can spot that it follows
 *  the following recurrence equation:
 *
 *  F(N) = (K-1) * F(N-1) + (K-1) * F(N-2) = (F(N-1) + F(N-2)) * (K-1)
 *
 *  The reason for this is not that hard to understand. When we add a new digit
 *  space, that slot can have (K-1) values, remember it cannot be 0. We can combine
 *  these (K-1) possibilites with all the sequences we found for F(N-1). The
 *  problem is that F(N-1) doesn't account for the scenarios where the first
 *  digit is 0. With this possibility, there are F(N-2) possible new sequences,
 *  that we have to add.
 *
 *  Looking at this function, you can see that it closely resembles the Fibonacci
 *  sequence. One of the fastest way to calculate this sequence is to convert it
 *  to matrix form[1].
 *
 *  The way to envision this is to say that we have:
 *
 *  L(N) = { { F(N+1), F(N) }, { F(N), F(N-1) } }
 *
 *  We want to find a matrix R such that:
 *
 *  L(N) * R = L(N+1)
 *
 *  It is easy to deduct that R must be:
 *
 *  R = { { K-1, 1 }, { K-1, 0 } }
 *
 *  Knowing this gives us the fact that
 *
 *  L(N) = L(1) * R^(N-1)
 *
 *  If we do the matrix exponation in the form of exponentation by squaring,
 *  we now have O(log(n)) operations.
 *
 *  However, for such small numbers as this, the normal approach is equally
 *  fast and requries less code, so I'm going for that here.
 *
 *  [1]: https://www.nayuki.io/page/fast-fibonacci-algorithms
 */

#include <stdio.h>
#include <inttypes.h>

#define TT uint_fast64_t

int main() {
	TT N, K;

	scanf("%" SCNuFAST64 "\n" "%" SCNuFAST64, &N,&K);

	// Now we just have to do the last little thing.
	// we set and b2 to K-1.
	// We therfor start at N = 2;
	TT b2 = 1;
	TT b1 = K-1;
	for (TT i = 1; i < N; i++) {
		TT tmp = (b1 + b2) * (K-1);
		b2 = b1;
		b1 = tmp;
	}

	printf("%" PRIuFAST64 "\n", b1);
	return 0;
}
