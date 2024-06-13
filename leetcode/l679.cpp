#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct pair_hash
{
  std::size_t operator()(const std::pair<int, int>& p) const { return ((std::size_t)p.first << 32) | p.second; }
};

class Solution
{
  using T = std::unordered_set<std::pair<int, int>, pair_hash>;
  using CACHE = std::unordered_map<std::pair<int, int>, T, pair_hash>;

  static T possible(const std::vector<int>& cards, CACHE& cache, const int start, const int end)
  {
    if (start + 1 == end) {
      return { { cards[start], 1 } };
    }

    const auto key = std::make_pair(start, end);
    if (const auto it = cache.find(key); it != cache.end()) {
      return it->second;
    }

    T out;
    const auto normalize = [&](const int nom, const int den) {
      if (den == 0) {
        return;
      }

      if (nom == 0) {
        out.emplace(0, 1);
      } else {
        const int g = std::gcd(nom, den);
        out.emplace(nom / g, den / g);
      }
    };

    // ok now then... we have paranthesis before and after. if we are at
    // start == 0, then the only prev action we are allowed to do is +

    for (int split = start + 1; split < end; split++) {
      const auto posLeft = possible(cards, cache, start, split);
      const auto posRight = possible(cards, cache, split, end);

      for (const auto& [ln, ld] : posLeft) {
        for (const auto& [rn, rd] : posRight) {
          // multiplication
          normalize(ln * rn, ld * rd);

          // division
          normalize(ln * rd, ld * rn);

          // addition
          normalize(ln * rd + rn * ld, ld * rd);

          // minus
          normalize(ln * rd - rn * ld, ld * rd);
        }
      }
    }

    cache.emplace(key, out);

    return out;
  }

public:
  static bool judgePoint24(std::vector<int>& cards)
  {
    std::ranges::sort(cards);
    CACHE cache;
    do {
      cache.clear();
      const auto pos = possible(cards, cache, 0, 4);
      if (pos.contains({ 24, 1 }))
        return true;
    } while (std::ranges::next_permutation(cards).found);

    return false;
  }
};
