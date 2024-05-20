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
  // static void nextPermutation(std::vector<int>& nums) { std::ranges::next_permutation(nums); }
  static void nextPermutation(std::vector<int>& nums)
  {
    int i = nums.size() - 2;
    while (0 <= i && nums[i + 1] <= nums[i]) {
      i--;
    }

    if (0 <= i) {
      int j = nums.size() - 1;
      while (nums[j] <= nums[i])
        j--;

      using std::swap;
      swap(nums[j], nums[i]);
    }

    using std::reverse;
    reverse(nums.begin() + i + 1, nums.end());
  }
};

int
main()
{
  return 0;
}
