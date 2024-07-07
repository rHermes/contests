#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  struct Item
  {
    int ss{ std::numeric_limits<int>::max() };

    std::uint16_t i{ 0 };
    std::uint16_t j{ 0 };

    constexpr auto operator<=>(const Item& other) const { return other.ss <=> ss; }
  };

public:
  static std::vector<std::vector<int>> kSmallestPairs(const std::vector<int>& nums1,
                                                      const std::vector<int>& nums2,
                                                      const int k)
  {
    const int N1 = nums1.size();
    const int N2 = nums2.size();

    std::vector<std::vector<int>> out(k);
    int idx = 0;

    std::priority_queue<Item> Q;
    Q.emplace(nums1[0] + nums1[0], 0, 0);

    while (idx < k) {
      auto top = Q.top();
      Q.pop();
      out[idx++] = { nums1[top.i], nums2[top.j] };

      if (top.i + 1 < N1) {
        const int ni = top.i + 1;
        const int nj = top.j;

        Q.emplace(nums1[ni] + nums2[nj], ni, nj);
      }

      // The 0 constraint here, makes sure we are only getting unique
      // combinations, without having a visited table. Very clever.
      if (top.i == 0 && (top.j + 1 < N2)) {
        const int ni = top.i;
        const int nj = top.j + 1;
        Q.emplace(nums1[ni] + nums2[nj], ni, nj);
      }
    }

    return out;
  }
};
