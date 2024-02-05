/**
 * 
 *
 * https://math.stackexchange.com/a/4801204
 * https://oeis.org/wiki/Simplicial_polytopic_numbers#Formulae
 *
 */
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <numbers>
#include <unordered_map>
#include <vector>
#include <iostream>

using ST = std::int64_t;
using UT = std::uint64_t;

constexpr UT MAX_N = 10 * 10 * 10 * 10 * 10 * 10;
constexpr UT MOD_M = 1000000007;

std::array<UT, MAX_N+1> factorial;

UT inverse(UT a) {
	if (a <= 1) {
		return a;
	} else {
		return MOD_M - static_cast<UT>(MOD_M/a) * inverse(MOD_M % a) % MOD_M;
	}
}

UT binomial_coefficient(UT n, UT k) {
	if (n < k)
		return 0;

	return factorial[n] * inverse(factorial[k] * factorial[n-k] % MOD_M) % MOD_M;
}

UT solve(UT N) {
  /* printf("Called S(%lu)\n", N); */
  UT ans = 0;
	const UT maxN = (N + 1) / 2;
  for (UT i = 1; i <= maxN; i++) {
		const UT left = N-i+1;
		const UT thisLen = binomial_coefficient(left - i + 1, i);
    ans = (ans + thisLen) % MOD_M;
  }

  /* printf("\n"); */
  return ans;
}

int main(void) {
	factorial[0] = 1;
	for (UT i = 1; i <= MAX_N; i++) {
		factorial[i] = (factorial[i-1] * i) % MOD_M;
	}
	

#ifdef ONLINE_JUDGE
  UT N;
  scanf("%lu", &N);
  printf("%lu\n", solve(N));
#else
  std::vector<std::pair<UT, UT>> testCases = {
      {1, 1},
      {2, 2},
      {3, 3},
      {4, 5},
      {5, 8},
      {6, 12},
      {7, 18},
      {8, 27},
      {9, 40},
      {10, 59},
      {20, 2744},
      {30, 125490},
      {100, 332959340},
      {1000, 708863357},
      {10 * 10 * 10 * 2, 327988819},
      {10*10*10*10, 997127326},
      {10*10*10*10*10, 34605689},
      {10*10*10*10*10*10, 474866529},
  };

  for (const auto &[input, shouldBe] : testCases) {
    const auto start = std::chrono::high_resolution_clock::now();

    const auto ans = solve(input);

    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diff = end - start;

    if (ans != shouldBe) {
      printf("Wrong answer for %lu, we calculated %lu, but it should be %lu\n", input, ans,
             shouldBe);
		} else {
			printf("S(%lu) took %.5f seconds to run\n", input, diff.count());
			/* std::cout << "Time to fill and iterate a vector of " << std::setw(9) << " ints : " << diff << '\n'; */
    }
  }
#endif

  return 0;
}
