/*
 *  p1012 - K-based Numbers. Version 2
 *
 *  This is just a copy of my solution to p. 1009, with big int support added.
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
 *  It is worth noteing that we only have to find L(N-1) to find F(N),
 *  as it will be included in the matrix.
 *
 *  If we do the matrix exponation in the form of exponentation by squaring,
 *  we now have O(log(n)) operations.
 *
 *  The L(1) part is equal to:
 *
 *  L(1) = { { K*(K-1), K-1 }, { K-1, 1} }
 *
 *
 *  An implementation of this in mathematica then is as simple as:
 *
 *  F[N_,K_] := ({{K*(K-1), K-1},{K-1, 1}}.MatrixPower[{{K-1,1},{K-1,0}}, N-2])[[1,1]] 
 *
 *  The largest value this can have is F[1790,10]. To make this easier
 *  and faster to implement, I've choosen to use a decimal base,
 *  and that base is: 10^9. This fits within u32_t and to find the
 *  highest we are going to need to go then, we just do
 *
 *  Ceiling[Log[10^9, F[1790, 10]]]
 *
 *  Which gives us 199 in Mathematica, but we raise this to 205 for
 *  good measure. This could have been done with a matrix algorithm,
 *  but instead I've choosen to use just use a normal one, as it
 *  is almost as fast, and uses less memory.
 *
 *
 *  [1]: https://www.nayuki.io/page/fast-fibonacci-algorithms
 */

#include <stdio.h>
#include <inttypes.h>

#define TT uint64_t

#define BIG_MAX 205
#define BIG_BASE 1000000000
/* Slow bigint implementation, that gets the job done. */
typedef uint32_t BIG[BIG_MAX];

// This adds big a and b together.
void BIG_add(BIG a, BIG b, BIG c) {
	uint32_t carry = 0;
	for (int i = 0; i < BIG_MAX; i++) {
		uint64_t tmp = (uint64_t)a[i] + (uint64_t)b[i] + carry;
		c[i] = tmp % BIG_BASE;
		carry = tmp / BIG_BASE;
	}
}

// This multiplies a * b into c
void BIG_mul(BIG a, uint32_t wow) {
	uint32_t carry = 0;
	for (int i = 0; i < BIG_MAX; i++) {
		uint64_t tmp = wow*(uint64_t)a[i] + carry;
		a[i] = tmp % BIG_BASE;
		carry = tmp / BIG_BASE;
	}
}


// THis is the matrix type.
typedef BIG BIG_MAT[2][2];

int main() {
	uint32_t N, K;

	scanf("%" SCNu32 "\n" "%" SCNu32, &N,&K);

	BIG b2 = {0};
	BIG b1 = {0};
	BIG tmp = {0};
	
	// We know that these are not going to be larger than the K value,
	// so we don't need to do any carefull consideration here.
	b2[0] = 1;
	b1[0] = K-1;

	uint32_t* pb1 = b1;
	uint32_t* pb2 = b2;
	uint32_t* ptmp = tmp;

	// we set and b2 to K-1.
	// We therfor start at N = 2;
	for (uint32_t i = 1; i < N; i++) {
		BIG_add(pb1,pb2,ptmp);
		BIG_mul(ptmp, K-1);

		uint32_t *lll = pb2;

		pb2 = pb1;
		pb1 = ptmp;
		ptmp = lll;
	}

	// Now the answer is in pb1. We figure it out by finding the length.
	int length;
	for (length = BIG_MAX-1; !pb1[length] && length >= 0; length--) {}

	printf("%" PRIu32, pb1[length--]);
	while (length >= 0) {
		printf("%.9" PRIu32, pb1[length--]);
	}
	printf("\n");

	return 0;
}
