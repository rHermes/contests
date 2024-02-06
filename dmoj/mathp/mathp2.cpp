/**
 * mathp2 - A Math Contest P2 - Subsequence Sum
 *
 * The question here, is to find the sum of all subsequence sums modulo 10^9 + 7
 *
 * The number of subsequences quickly explode, but we can find a really cool insight,
 * by looking at the inclusion of each number in the subsequence as binary. We can
 * get all subsequences then by iterating through all the binary numbers. An example
 * to illustrate, with 1, 2 and 3:
 *
 *    +   +   | 000
 *    +   + 1 | 001
 *    + 2 +   | 010
 *    + 2 + 1 | 011
 *  3 +   +   | 100
 *  3 +   + 1 | 101
 *  3 + 2 +   | 110
 *  3 + 2 + 1 | 111
 *
 * The crucial insight here, is how many times each number appears. As they are
 * represented with a bit in our binary number, they appear in exactly half the
 * subsequences. That means we can write this as:
 *
 * 2^(3-1) * 3 + 2^(3-1) * 2 + 2^(3-1)*1 = 2^(3-1) * (1 + 2 + 3)
 *
 * This is really cool, as it allows us to just sum together the numbers we get in
 * and multiply that sum by 2^(N-1) at the end, to get the solution! This makes the
 * solution O(N).
 *
 * --------------------------------------------------------------------
 *
 * If we are not able to gain this insight, the problem can also be solved dynamically.
 * We define f(n) as the sum of all possible subsequences of the array elements a[1],
 * a[2], ..., a[n]
 *
 * We then have:
 *
 * f(1) = a[1]
 *
 * This is the base case. For the next case we have:
 *
 * f(n) = 
 *	f(n-1) # The part where we don't include a[n]
 *	+
 *	f(n-1) # The parts when we do include a[n]
 *	+
 *	2^(n-1) * a[n] # The number of new a[n]'s we are including.
 *
 *	This approach requires more calculation, but it's another way
 *	to arrive at the answer.
 *
 * ---------------------------------------------------------------------
 *
 *  One cool digression here, is that if it was the products of all subsets
 *  the formula is instead:
 *
 *     = a + b + ab 
 *		 = a(1+b) + b + 1 - 1 
 *		 = a(1+b) + (1+b) - 1 
 *		 = (a + 1) * (b + 1) - 1
 *		 = (1+a) * (1 + b) - 1
 *
 *	And for three:
 *
 *	   = a + b + c + ab + bc + ca + abc 
 *     = a + ac + b + bc + ab + abc + c + 1 - 1
 *     = a(1+c) + b(1+c) + ab(1+c) + c + 1 - 1
 *     = (a + b + ab + 1)(1+c) - 1 
 *     = (1+a) * (1+b) * (1+c) - 1
 *
 *  But we can also do:
 *
 *  f(n) = 
 *		f(n-1) # Case were we don't include a[n]
 *		+
 *		f(n-1)*a[n] # Case where we include a[n]
 *		+
 *		a[n]       # Case where we have a[n] alone.
 *
 *	I love that these problems have such elegant solutions
 */
#include <cstdio>
#include <cstdint>

using ST = std::int64_t;
using UT = std::uint64_t;

const UT MOD_M = 1000000007;

inline ST pmod(ST i, ST n) {
    return (i % n + n) % n;
}

ST ipow(ST base, UT exp, UT m) {
	ST res = 1;
	base = pmod(base, m);

	if (base == 0)
		return 0;

	while (exp > 0) {
		if (exp % 2 == 1)
			res = pmod(res * base, m);

		exp >>= 1;
		base = pmod(base*base, m);
	}

	return res;
}


int main(void) {
	UT N;
	scanf("%lu", &N);

	const UT gotit = ipow(2, N-1, MOD_M);

	UT ans = 0;
	for (UT i = 0; i < N; i++) {
		UT x;
		scanf("%ld", &x);
		ans = (ans + x) % MOD_M;
	}

	printf("%ld\n", (ans * gotit) % MOD_M);

	return 0;
}
