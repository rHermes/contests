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
  static int findLength(const std::vector<int>& nums1, const std::vector<int>& nums2)
  {
    const int N = nums1.size();
    const int M = nums2.size();

    std::vector<int> prevDP(M, 0);
    std::vector<int> curDP(M, 0);

    int ans = 0;
    for (int j = 0; j < M; j++) {
      if (nums1[0] == nums2[j]) {
        curDP[j] = 1;
        ans = 1;
      }
    }

    for (int i = 1; i < N; i++) {
      std::swap(prevDP, curDP);

      curDP[0] = nums1[i] == nums2[0];
      for (int j = 1; j < M; j++) {
        if (nums1[i] == nums2[j]) {
          curDP[j] = 1 + prevDP[j - 1];
          ans = std::max(ans, curDP[j]);
        } else {
          curDP[j] = 0;
        }
      }
    }

    return ans;
  }
};
