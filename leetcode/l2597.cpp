#include <algorithm>
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
  using IT = std::vector<int>::iterator;

  static int helper(IT beg, IT end, int k)
  {
    if (beg == end)
      return 1;

    if (beg + 1 == end)
      return 2;

    const int x = *(--end);

    const auto sec = std::partition(beg, end, [&](const int y) { return (y != x + k) && (y != x - k); });

    if (sec == end) {
      return 2 * helper(beg, end, k);
    } else {
      return helper(beg, sec, k) + helper(beg, end, k);
    }
  }

public:
  static int beautifulSubsets(std::vector<int>& nums, int k) { return helper(nums.begin(), nums.end(), k) - 1; }
};

int
main()
{
  return 0;
}
