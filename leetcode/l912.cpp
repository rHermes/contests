
#include <iostream>
#include <ranges>
#include <vector>
inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  template<std::ranges::random_access_range R>
  static constexpr auto getPivot(R&& r)
  {
    const auto a = r.front();
    const auto b = r[r.size() / 2];
    const auto c = *(r.end() - 2);

    if (a < b) {
      if (b < c) {
        return b;
      } else if (c < a) {
        return a;
      } else {
        return c;
      }
    } else {
      if (c < b) {
        return b;
      } else if (c < a) {
        return a;
      } else {
        return c;
      }
    }
  }

  template<std::ranges::random_access_range R>
  static constexpr void sortIt(R&& r)
  {
    // We need to
    const auto sz = std::ranges::size(r);
    if (sz <= 1) {
      return;
    }
    if (sz == 2) {
      if (r[1] < r[0])
        std::swap(r[0], r[1]);
      return;
    }

    // pivot element is going to be the midway.
    const auto val = getPivot(r);
    const auto beg = std::ranges::begin(r);
    const auto end = std::ranges::end(r);

    auto left = beg;
    auto right = end - 1;
    while (true) {
      while ((*left) < val) {
        left++;
      }

      while (val < (*right)) {
        right--;
      }

      if (right <= left)
        break;

      std::swap(*left, *right);
      left++;
      right--;
    }

    const auto pi = right + 1;
    const auto leftRange = std::ranges::subrange(beg, pi);
    const auto rightRange = std::ranges::subrange(pi, end);

    sortIt(leftRange);
    sortIt(rightRange);
  }

public:
  static constexpr std::vector<int> sortArray(std::vector<int>& nums)
  {
    sortIt(nums);
    return std::move(nums);
  }
};
