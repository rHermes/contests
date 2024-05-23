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
  using T = std::array<int, 20>;

  static int helper(T& nums, int sz, int k)
  {
    if (sz == 0)
      return 1;

    if (sz == 1)
      return 2;

    T s{};

    sz--;
    int x = nums[sz];
    int xz = 0;
    for (int i = 0; i < sz; i++) {
      if (nums[i] != x + k && nums[i] != x - k)
        s[xz++] = nums[i];
    }

    if (sz == xz) {
      return 2 * helper(nums, sz, k);
    } else {
      return helper(nums, sz, k) + helper(s, xz, k);
    }
  }

public:
  static int beautifulSubsets(std::vector<int>& nums, int k)
  {
    T hey;
    std::copy(nums.begin(), nums.end(), hey.begin());
    int sz = nums.size();
    return helper(hey, sz, k) - 1;
  }
};

int
main()
{
  return 0;
}
