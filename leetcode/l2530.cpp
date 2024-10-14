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
public:
  static long long maxKelements(std::vector<int>& nums, const int k)
  {
    // We just do this inplace, since it's leetcode.
    std::ranges::make_heap(nums);

    long long score = 0;
    int i = 0;
    while (i < k) {
      std::ranges::pop_heap(nums);
      do {
        i++;
        score += nums.back();
        nums.back() = (nums.back() + 2) / 3;
      } while (i < k && (nums.front() <= nums.back()));

      std::ranges::push_heap(nums);
    }
    return score;
  }
};
