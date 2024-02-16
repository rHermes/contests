/* Managed to solve this by realizing that the
 * least amount of swaps needed to solve any number
 * is always just to focus on moving the smallest
 * element to the front of the list.
 *
 * steps_to_solve((3, 4, 2, 1))    -> 3 swaps to get 1 to the front
 * 3 + steps_to_solve((3, 4, 2))   -> 2 swaps to get 2 to the front
 * 3 + 2 + steps_to_solve((3, 4))  -> 0 swaps to get 3 to the front
 * 3 + 2 + 0 + steps_to_solve((4)) -> 0 swaps to get 4 to the front
 * 3 + 2 + 0 + 0 = 5 
 *
 * I verified this behavior with a brute force checker for
 * smaller Ns in python and it checks out. I cannot
 * mathemathically prove this, but it's good enough for me.
 *
 * Now we need to turn this problem around and ask ourselves
 * how many of each can be sorted in a number of steps. If we
 * define F(N, K) as the number of number of permutations we
 * can sort with K swaps of adjecent elements, then we realize
 * that we can always treat this as solving for the smallest 
 * first.
 *
 * Let's look at an example to see the idea. We take N=4.
 * In this permutation 1 can be in 4 places. To sort each
 * of these, we are first going to move 1 to the front, so
 * it will take atleast:
 *
 * (1, _, _, _) -> 0 swaps
 * (_, 1, _, _) -> 1 swaps
 * (_, _, 1, _) -> 2 swaps
 * (_, _, _, 1) -> 3 swaps
 *
 * This means that if we first do those swaps, we must then
 * just see how many ways we can sort the remaining elements.
 * This gives us a recursive definition for F:
 *
 * (1, _, _, _) -> 0 swaps -> F(3, K)
 * (_, 1, _, _) -> 1 swaps -> F(3, K-1)
 * (_, _, 1, _) -> 2 swaps -> F(3, K-2)
 * (_, _, _, 1) -> 3 swaps -> F(3, K-3)
 *
 * With some edge conditions, like F(N, 0) = 1, we can actually
 * solve it like this. I tried to do this, with introducing caching
 * on the (N,K) level, but this was to slow.
 *
 * We realize that since we are always summing up ranges of items above,
 * we can use summation tables to speed this up. It took some time to get
 * there for me with the implementation, but once I did, it worked!
 *
 * Some other notes is that the maximum number of swaps needed to solve
 * any one of them is M(n) = (n*(n-1))/2. If K is larger than this, we
 * can just remove 2 from it until it's lower and get the same answer,
 * as it would amount to just swapping elements back and forth. This was
 * important in order to reduce the number of calls in the initial version,
 * but wasn't used much in the final version, as we just skipped it.
 *
 */
#include <cstdio>
#include <cstdint>
#include <vector>

#include <map>
#include <numbers>
#include <cmath>

using ST = std::int64_t;
using UT = std::uint64_t;

constexpr UT MOD_M = 1000000007;
/* constexpr UT MAX_N  = 3000; */

inline ST pmod(ST i, ST n) {
	return (i % n + n) % n;
}

UT findGoodK(const UT N, const UT K) {
	// This is the maximum number of steps it can take to reach any permutation.
	// It corresponds to the number of steps to reach the complete reverse of
	// the sorted tuple. (1,2,3,4) has the worst case (4, 3, 2, 1)
	const UT M = (N * (N-1)) / 2;

	if (K <= M)
		return K;
	else
		return M - ((K - M) % 2);
}

std::map<std::pair<UT,UT>, UT> cache;
UT solve(const UT N, const UT K) {
	if (K == 0)
		return 1;

	if (N <= 1)
		return 0;

	// We are reducing the number of steps here. I am sure there are a faster
	// way to do this, but for now this will do
	UT k = findGoodK(N, K);
	const auto cacheKey = std::make_pair(N, k);
	

	if (auto it = cache.find(cacheKey); it != cache.end()) {
		return it->second;
	}

	// Ok, it's not in the cache.

	/* const UT M = (N * (N-1)) / 2; */
	UT ans = 0;

	for (UT i = 0; i <= std::min(N-1, k); i++) {
		ans = (ans + solve(N-1, k-i)) % MOD_M;
	}

	cache.emplace(std::move(cacheKey), ans);
	return ans;
}

/* std::map<std::pair<UT,UT>, UT> sumTable; */
UT solveSumTable(const UT N, const UT K) {
	if (K == 0)
		return 1;

	if (N <= 1)
		return 0;

	// It doesn't hurt to reduce K as much as possible, since our runtime scales
	// with it. For larger values of N, this is not really going to matter, but
	// we take any small win we can.
	const UT nK = findGoodK(N, K);

	// We actually only need the previous row, as we are never looking longer back.
	// This means our memory only scales with K, which is very nice.
	const UT rowSize = (nK+2);
	std::vector<ST> sumTable((N+1)*rowSize);
	
	// We fill the two row
	for (UT col = 0; col <= nK; col++)
		sumTable[2*rowSize + col] = (col + 1) % MOD_M;

	for (UT row = 3; row <= N; row++) {
		sumTable[row*rowSize] = 1;

		for (UT col = 1; col <= nK; col++) {
			const UT maxK = col;
			if (row-1 < maxK) {
				// We are going from (maxK - (row-1)) to (maxK)
				sumTable[row*rowSize + col] = pmod(
						sumTable[row*rowSize + col - 1] // previous
						+ sumTable[(row-1)*rowSize + maxK] // sum up to maxK
						- sumTable[(row-1)*rowSize + (maxK - row + 1) - 1] // sum up to (maxK - (row-1) -1)
						, MOD_M);
			} else {
				// We are going from (0 to maxK)
				sumTable[row*rowSize + col] = pmod(sumTable[row*rowSize + col - 1] + sumTable[(row-1)*rowSize + col], MOD_M);
			}
		}
	}
	

	return static_cast<UT>(pmod(sumTable[N*rowSize + nK] - sumTable[N*rowSize + nK - 1], MOD_M));
}

int main(void) {
#ifdef ONLINE_JUDGE
	UT N, K;
	scanf("%lu %lu", &N, &K);

	printf("%lu\n", solveSumTable(N, K));
#else
	/* printf("%lu should be %lu\n", solveSumTable(3, 3), 3L); */
	/* printf("%lu should be %lu\n", solveSumTable(7, 6), 378L); */
	/* printf("%lu should be %lu\n", solve(100, 40), 806588704L); */
	/* printf("%lu should be %lu\n", solveSumTable(100, 40), 806588704L); */
	/* printf("%lu should be %lu\n", solve(100, 100), 814710884L); */
	/* printf("%lu should be %lu\n", solve(3000, 100), 212099000L); */
	/* printf("%lu should be %lu\n", solveSumTable(3000, 100), 212099000L); */

	/* for (const auto& [k, v] : cache) { */
	/* 	printf("F(%lu, %lu) = %lu\n", k.first, k.second, v); */
	/* } */
#endif


	return 0;
}
