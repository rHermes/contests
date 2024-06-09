#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  [[nodiscard]] constexpr static bool canBeDone(const std::vector<std::int64_t>& psa,
                                                const std::size_t k,
                                                const std::int64_t target)
  {
    if (target < psa.front())
      return false;

    std::size_t buckets = 1;
    auto it = std::upper_bound(psa.cbegin(), psa.cend(), target);
    while (it != psa.cend()) {
      buckets++;
      if (k < buckets)
        return false;

      it = std::upper_bound(it, psa.cend(), *(it - 1) + target);
    }

    return true;
  }

  int splitArray(std::vector<int>& nums, int k)
  {
    std::vector<std::int64_t> psa(nums.size());
    psa[0] = nums[0];
    std::int64_t lowerBound = 0;
    for (std::size_t i = 1; i < nums.size(); i++) {
      psa[i] = psa[i - 1] + nums[i];
      lowerBound = std::max(lowerBound, static_cast<std::int64_t>(nums[i]));
    }

    if (lowerBound == 0)
      return 0;

    if (k == 1)
      return static_cast<int>(psa.back());

    std::int64_t upperBound = psa.back();
    // as we always want the lowerbound to be less than the actual answer
    lowerBound--;

    while (lowerBound + 1 < upperBound) {
      const auto mid = (lowerBound + upperBound) / 2;

      if (canBeDone(psa, static_cast<std::size_t>(k), mid)) {
        upperBound = mid;
      } else {
        lowerBound = mid;
      }
    }

    return static_cast<int>(upperBound);
  }
};
