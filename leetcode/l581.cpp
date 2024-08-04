#include <iostream>
#include <limits>
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
  static constexpr int findUnsortedSubarray(const std::vector<int>& nums)
  {
    const int N = nums.size();

    // Find the left most item with greater elemnts to the right;
    int hasBiggerLeft = -1;
    int mmax = std::numeric_limits<int>::lowest();
    for (int i = 0; i < N; i++) {
      if (nums[i] < mmax) {
        hasBiggerLeft = i;
      } else {
        mmax = nums[i];
      }
    }
    if (hasBiggerLeft == -1)
      return 0;

    int hasSmallerRight = 0;
    int mmin = std::numeric_limits<int>::max();
    for (int i = N - 1; 0 <= i; i--) {
      if (mmin < nums[i]) {
        hasSmallerRight = i;
      } else {
        mmin = nums[i];
      }
    }

    return hasBiggerLeft - hasSmallerRight + 1;
  }
};
