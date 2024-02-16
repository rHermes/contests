/**
 * nwerc11a - ICPC NWERC 2011 A - Binomial Coefficients
 *
 * This one has a really cool solution, that I had to google
 * to solve, but once you understand the idea, it is quite
 * simple.
 *
 * So the first way to realize this is to put up pascals triangle:
 *
 * (0,0) (1,1) (2,2) (3,3) (4,4) (5,5)
 * (1,0) (2,1) (3,2) (4,3) (5,4) 
 * (2,0) (3,1) (4,2) (5,3)   
 * (3,0) (4,1) (5,2)   
 * (4,0) (5,1)    
 * (5,0)    
 *
 * Since we have the identity:
 *
 * nCk = nC(n-k)
 *
 * There is symmetry in the triangle. We know that the input
 * cannot be 0 or 1, so everything with a k = 0, is gone. This
 * means we remove the first "column" in the triangle above,
 * and also the first "row". This leaves us with the following
 * triangle:
 *
 * (2,1) (3,2) (4,3) (5,4) 
 * (3,1) (4,2) (5,3)   
 * (4,1) (5,2)   
 * (5,1)    
 *
 * We have eliminated k=0 then, and we now look at k = 1. Here there
 * will always be the solution (X,1) and (X, X-1). But instead of
 * serving this as a special case, we will try to develop a method
 * to apply.
 *
 * If we fix K, then for all 0 < k, f(n) becomes an increasing function.
 * This means that there can be at most one n, that will make f(n) = X.
 *
 * Since it's ever increasing, we can use a binary search to look for
 * this n. This is easy to implement.
 *
 * The vital insight here, is that when we use f(n) to search through
 * a column "k", we are also searching through the corresponding row
 * in the triangle, given that we have the symmetry. This means that
 * once we have searched through f(n) with a k=1, we have the following
 * triangle left:
 *
 * (4,2) (5,3)   
 * (5,2)   
 * 
 * We can repeat the process for k=2 now. If we look at the starting points
 * for our searches here, we will see that they will be:
 *
 * k = 1: (2, 1)
 * k = 2: (4, 2)
 * k = 3: (6, 3)
 * k = 4: (8, 4)
 * k = 5: (10, 5)
 * ...
 *
 * The pattern is pretty clear here, they are (2k)Ck, also called:
 * "Central binomial coefficients".
 *
 * With this in mind, we know that the lower bound for our binary search
 * for f(n) will be f(2k). Since f is increasing, if f(2k) is larger than X,
 * then we can stop our search. Every element after this will be larger.
 *
 * This is fast enough, but we can do some cool(TM) things with inequalities,
 * to speed things up.
 *
 * We have the following inequality:
 *
 * (n-k)^k / k! <= nCk = n^k / k!
 *
 * This is true, because:
 *
 * nCk = (n * (n-1) * ... * (n - (k - 1))) / k!
 *
 * In other words, there will be k terms in the dividend, and
 * each of these are equal or smaller than "n" and each of them
 * are equal or larger than n-k.
 *
 * Once we have that, and using X = nCk we have:
 *
 * (n-k)^k <= X * k! <= n^k
 *
 * n - k <= (X * k!)^(-k) <= n
 *
 * From this we can get the following inequality:
 *
 * (X * k!)*(-k) <= n <= (X * k!)^(-k) + k
 *
 * So for a fixed k, we only have to check at most
 * k+1 values of n. They are also sequential, so we
 * can very quickly calculate them, using:
 *
 * comb(n, k) = comb(n-1, k) * (n+1)/(n+1-k)
 *
 * Now we don't have to do a binary search anymore for
 * X directly. Instead we do it to find the smallest
 * possible n, that satisfies the inequality above.
 *
 * To avoid floating point error in the square root,
 * we rephrase it to:
 *
 * X * k! <= pow(n, k)
 *
 * And we find the smallest n, for which this is true,
 * using a binary search.
 *
 * Another thing we can do to speed up the testing, is
 * to use the fact that:
 *
 * 4^n/2n <= comb(2n, n)
	*
 * As shown in [1], To speed up the check for if
 *
 * comb(2k, k) <= X
 *
 * [1]: https://en.wikipedia.org/wiki/Proof_of_Bertrand%27s_postulate#Lemma_1
 *
 * With all that said, we won't use this here, as the X * k!
 * multiplication easily overflows. But if you want to see
 * this approach, you can look at nwerc11a.py, which is also
 * in this directory.
 *
 *
 * The stackoverflow posts that I initially used:
 *
 * - https://math.stackexchange.com/a/103385
 * - https://math.stackexchange.com/a/2381576 
 *
 *
 *  Other sources used:
 *  - https://en.wikipedia.org/wiki/Pascal%27s_triangle
 *  - https://en.wikipedia.org/wiki/Binomial_coefficient
 *  - https://en.wikipedia.org/wiki/Central_binomial_coefficient
 *  - https://en.wikipedia.org/wiki/Proof_of_Bertrand%27s_postulate#Lemma_1
 *
 */

#include <cstdio>
#include <cstdint>

#include <limits>
#include <set>
#include <utility>

using UT = std::uint64_t;
using ST = std::int64_t;

UT comb(UT n, UT k) {
	UT c = 1;

	 if (n-k < k) // take advantage of symmetry
    k = n-k;

  for (UT i = 1; i <= k; i++, n--) {
    c = c / i * n + c % i * n / i; // split c * n / i into (c / i * i + c % i) * n / i
  }

  return c;
}

void solve(const UT X) {
	std::set<std::pair<UT,UT>> answers;

	for (UT k = 1; comb(2*k, k) <= X; k++) {
		// Binary search
		UT lo = 2*k-1;
		UT hi = 2*k;
		while (comb(hi, k) < X)
			hi *= 2;

		while (1 < hi - lo) {
			const UT mid = (hi + lo) / 2;
			if (comb(mid, k) < X)
				lo = mid;
			else
				hi = mid;
		}

		// We have to remember that there is symmetry and therefore, we need to
		// insert comb(n, k) and comb(n, n-k)
		if (comb(hi, k) == X) {
				answers.emplace(hi, k);
				answers.emplace(hi, hi - k);
		}
	}

	printf("%lu\n", answers.size());
	for (const auto& [n, k] : answers) {
		printf("(%lu,%lu) ", n, k);
	}
	printf("\n");
}


int main(void) {
	UT testcases;
	scanf("%lu", &testcases);

	for (UT ncase = 0; ncase < testcases; ncase++) {
		UT M;
		scanf("%lu", &M);
		solve(M);
	}
}
