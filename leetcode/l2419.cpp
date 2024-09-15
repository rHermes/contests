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
  int longestSubarray(const std::vector<int>& nums)
  {
    // A simple state machine approach.
    int biggest = nums[0];
    int longest = 1;
    int current = 1;

    for (int i = 1; i < static_cast<int>(nums.size()); i++) {
      if (nums[i] < biggest) {
        current = 0;
      } else if (nums[i] == biggest) {
        current++;
        longest = std::max(longest, current);
      } else {
        biggest = nums[i];
        longest = 1;
        current = 1;
      }
    }
    return longest;
  }
};
