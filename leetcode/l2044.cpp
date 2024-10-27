#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static int solve(const int target, const auto& nums, const int N, const int idx, const int cur)
  {
    if (cur == target) {
      // so now then. All elements after this, can be mixed and matched freely.
      return 1 << (N - idx);
    }

    if (idx == N) {
      return 0;
    }

    return solve(target, nums, N, idx + 1, cur | nums[idx]) + solve(target, nums, N, idx + 1, cur);
  }

public:
  static int countMaxOrSubsets(const std::vector<int>& nums)
  {
    // ok, this is stupid. The maximum OR is always going to be the total OR. So the question is to
    // see how many we can remove without triggering a bit to be lost.
    [[assume(nums.size() <= 16)]];
    const int N = nums.size();

    const int target = std::reduce(nums.begin(), nums.end(), 0, std::bit_or{});

    return solve(target, nums, N, 0, 0);
  }
};
