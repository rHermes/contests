#include <vector>

class Solution
{
public:
  int firstMissingPositive(std::vector<int>& nums)
  {
    // Ok, we can actually solve this, by sorting the array as we go, but only caring about
    // the items that are
    const auto n = nums.size();

    for (std::size_t i = 0; i < n; i++) {
      // we continue switching until the current items are wrong
      while (1 <= nums[i] && nums[i] <= static_cast<int>(n) && nums[static_cast<std::size_t>(nums[i]) - 1] != nums[i]) {
        std::swap(nums[static_cast<std::size_t>(nums[i]) - 1], nums[i]);
      }
    }

    // Now we can just find the first index who doesn't match.
    for (std::size_t i = 0; i < n; i++) {
      if (nums[i] != static_cast<int>(i + 1)) {
        return static_cast<int>(i + 1);
      }
    }
    return static_cast<int>(n + 1);
  }
};

int
main()
{
  return 0;
}
