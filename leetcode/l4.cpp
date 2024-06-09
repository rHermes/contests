#include <iostream>
#include <limits>
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
  static int findKthElement(const std::vector<int>& nums1,
                            const std::vector<int>& nums2,
                            const int start1,
                            const int start2,
                            const int k)
  {

    const int len1 = nums1.size();
    const int len2 = nums2.size();
    // ok, so let's think critically here.
    if (len1 <= start1) {
      // we must be in the right array
      return nums2[start2 + k - 1];
    }

    if (len2 <= start2) {
      return nums1[start1 + k - 1];
    }

    // We are looking for the first element
    if (k == 1) {
      return std::min(nums1[start1], nums2[start2]);
    }

    // ok, so now we have the new middle K
    const auto midK = k / 2;

    const auto idx1 = start1 + midK - 1;
    const auto idx2 = start2 + midK - 1;

    const auto val1 = (idx1 < len1) ? nums1[idx1] : std::numeric_limits<int>::max();
    const auto val2 = (idx2 < len2) ? nums2[idx2] : std::numeric_limits<int>::max();

    // Ok, so the idea is that if val1 < val2, then the kth element, cannot
    // be in the first midK elements of nums1, because the value will be
    // bigger than val2.
    if (val1 < val2) {
      return findKthElement(nums1, nums2, start1 + midK, start2, k - midK);
    } else {
      return findKthElement(nums1, nums2, start1, start2 + midK, k - midK);
    }
  }

public:
  static double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2)
  {

    const int len1 = nums1.size();
    const int len2 = nums2.size();

    if ((len1 + len2) % 2 == 0) {
      // For
      const int a = findKthElement(nums1, nums2, 0, 0, (len1 + len2 + 1) / 2);
      const int b = findKthElement(nums1, nums2, 0, 0, (len1 + len2 + 2) / 2);
      return std::midpoint<double>(a, b);
    } else {
      return findKthElement(nums1, nums2, 0, 0, (len1 + len2 + 1) / 2);
    }
  }
};
