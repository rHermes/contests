#include <array>
#include <cstdint>

using T = std::int64_t;
constexpr T MAXN = 202;
// To make sure we don't overflow
constexpr T MODN = 2000000011;

// We precompute the whole table.
constexpr std::array<T, MAXN * MAXN> binom = [] {
  std::array<T, MAXN * MAXN> comb{};

  comb[0] = 1;
  for (T i = 1; i < MAXN; i++) {
    comb[i * MAXN] = 1;
    comb[i * MAXN + i] = 1;
    for (T j = 1; j < i; j++) {
      comb[i * MAXN + j] = (comb[(i - 1) * MAXN + (j - 1)] + comb[(i - 1) * MAXN + j]) % MODN;
    }
  }
  return comb;
}();

class Solution
{

public:
  static constexpr int uniquePaths(const int m, const int n)
  {
    // this is just a combinatorial question. How many ways can we permute
    // a string of `m` Ds and `n` Rs.
    return 1 * binom[(m + n - 2) * MAXN + (n - 1)];
  }
};

int
main()
{
  return 0;
}
