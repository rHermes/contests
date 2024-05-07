#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

struct pcg32_random_r
{
  std::uint64_t state;
  std::uint64_t inc;

  using result_type = std::uint32_t;

  static result_type min() { return 0; }
  static result_type max() { return std::numeric_limits<result_type>::max(); }

  result_type operator()()
  {
    std::uint64_t oldstate = state;
    // Advance internal state
    state = oldstate * 6364136223846793005ULL + (inc | 1);
    // Calculate output function (XSH RR), uses old state for max ILP
    std::uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    std::uint32_t rot        = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
  }
};

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  pcg32_random_r rng;
  std::discrete_distribution<int> dist;
  Solution(std::vector<int>& w) : rng{ 123, 123 }, dist(w.begin(), w.end()) {}

  int pickIndex() { return dist(rng); }
};

int
main()
{
  return 0;
}
