#include <array>
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
  static std::vector<int> intersect(const std::vector<int>& nums1, const std::vector<int>& nums2)
  {
    constexpr int MAXN = 10000;
    std::array<int, MAXN + 1> counter{};

    std::vector<int> out;
    out.reserve(nums1.size() + nums2.size());
    for (const auto x : nums1)
      counter[x]++;

    for (const auto x : nums2) {
      if (0 <= --counter[x])
        out.push_back(x);
    }

    return out;
  }
};
