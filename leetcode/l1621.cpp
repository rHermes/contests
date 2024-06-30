#include <cstdint>

class Solution
{

  using UT = std::int64_t;
  static constexpr UT MODN = 1000000007;

  static constexpr UT invMod(UT a)
  {
    if (a <= 1) {
      return a;
    } else {
      return MODN - (UT)(MODN / a) * invMod(MODN % a) % MODN;
    }
  }

public:
  static constexpr int numberOfSets(const int N, const int K)
  {

    // We are transforming this into a pick "from n pick k" task,
    // by adding k-1 virtual points.
    const int NEW_N = N + K - 1;
    const int NEW_K = 2 * K;
    UT above = 1;
    UT below = 1;

    for (UT i = 1; i <= NEW_K; i++) {
      above = (above * (NEW_N - NEW_K + i)) % MODN;
      below = (below * i) % MODN;
    }

    return (above * invMod(below)) % MODN;
  }
};
