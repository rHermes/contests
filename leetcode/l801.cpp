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
  static constexpr int minSwap(const std::vector<int>& nums1, const std::vector<int>& nums2)
  {
    const int N = nums1.size();

    int curSwaps = 1;
    int curNoSwaps = 0;

    for (int i = N - 2; 0 <= i; i--) {
      const auto nextNoSwap = curNoSwaps;
      const auto nextYesSwap = curSwaps;

      curNoSwaps = N;
      curSwaps = N;

      if (nums1[i] < nums1[i + 1] && nums2[i] < nums2[i + 1]) {
        // Now we did no switch
        curNoSwaps = nextNoSwap;
        curSwaps = 1 + nextYesSwap;
      }

      if (nums1[i] < nums2[i + 1] && nums2[i] < nums1[i + 1]) {
        curNoSwaps = std::min(curNoSwaps, nextYesSwap);
        curSwaps = std::min(curSwaps, 1 + nextNoSwap);
      }
    }

    return std::min(curNoSwaps, curSwaps);
  }
};
