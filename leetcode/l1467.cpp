#include <cmath>
#include <cstdlib>
#include <numeric>
#include <unordered_map>
#include <vector>

template<typename T, typename... Rest>
void
hash_combine(std::size_t& seed, const T& v, const Rest&... rest)
{
  seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  (hash_combine(seed, rest), ...);
}

class Solution
{
  using T = double;

  // sumLeft, sumRight, spotBal, distBal, idx
  using UT = std::tuple<int, int, int, int, int>;

  struct int_tuple_hash
  {
    std::size_t operator()(const UT& p) const
    {
      const auto& [a, b, c, d, e] = p;
      std::size_t seed = 0;
      hash_combine(seed, a, b, c, d, e);

      return seed;
    }
  };

  using CT = std::unordered_map<UT, double, int_tuple_hash>;

  static T getGood(const std::vector<int>& balls,
                   const int N2,
                   const std::vector<T>& binom,
                   CT& cache,
                   const int sumLeft,
                   const int sumRight,
                   const int spotBal,
                   const int distBal,
                   int idx)
  {
    const int K = balls.size();
    const int ROW = N2 + 1;

    // So here are the axis we can cache on:
    // let's try?

    // ok, so we are going to check here.
    if (idx == K) {
      return spotBal == 0 && distBal == 0;
    }

    if (N2 / 2 < std::abs(spotBal))
      return 0;

    if (K - idx < std::abs(distBal))
      return 0;

    const auto key = std::make_tuple(sumLeft, sumRight, spotBal, distBal, idx);
    if (auto it = cache.find(key); it != cache.end()) {
      return it->second;
    }

    const int tot = balls[idx];

    T ans = 0;
    for (int i = 0; i <= tot; i++) {
      const T scale = binom[(sumLeft + i) * ROW + i] * binom[(sumRight + (tot - i)) * ROW + tot - i];
      if (i == 0) {
        ans += scale *
               getGood(balls, N2, binom, cache, sumLeft, sumRight + tot, spotBal + (2 * i - tot), distBal - 1, idx + 1);
      } else if (i == tot) {
        ans += scale *
               getGood(balls, N2, binom, cache, sumLeft + tot, sumRight, spotBal + (2 * i - tot), distBal + 1, idx + 1);
      } else {
        ans +=
          scale *
          getGood(balls, N2, binom, cache, sumLeft + i, sumRight + tot - i, spotBal + (2 * i - tot), distBal, idx + 1);
      }
    }

    cache.emplace(key, ans);

    return ans;
  }

public:
  static double getProbability(const std::vector<int>& balls)
  {
    const int K = balls.size();
    const int N2 = std::reduce(balls.begin(), balls.end(), 0);

    const int ROW = N2 + 1;
    std::vector<T> binom(ROW * ROW, 0);
    for (int nn = 0; nn < ROW; nn++) {
      binom[nn * ROW] = 1;
      binom[nn * ROW + nn] = 1;

      for (int kk = 1; kk < nn; kk++) {
        binom[nn * ROW + kk] = binom[(nn - 1) * ROW + (kk - 1)] + binom[(nn - 1) * ROW + kk];
      }
    }

    CT cache;
    T good = getGood(balls, N2, binom, cache, 0, 0, 0, 0, 0);

    // total ways
    T ways = 1;
    int sum = 0;
    for (int i = 0; i < K; i++) {
      sum += balls[i];
      ways *= binom[sum * ROW + balls[i]];
    }
    return good / ways;
  }
};
