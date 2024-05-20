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
  static void twoSum(const std::vector<int>& nums,
                     const int K,
                     std::vector<std::vector<int>>& out,
                     const long target,
                     const int start)
  {
    const int N = nums.size();
    int lo = start;
    int hi = N - 1;
    while (lo < hi) {
      int curr_sum = nums[lo] + nums[hi];

      if (curr_sum < target || (start < lo && nums[lo - 1] == nums[lo])) {
        ++lo;
      } else if (target < curr_sum || (hi < N - 1 && nums[hi] == nums[hi + 1])) {
        --hi;
      } else {
        // we are now pushing back.
        auto& vec = out.emplace_back(K, 0);
        vec[K - 1] = nums[hi];
        vec[K - 2] = nums[lo];
        hi--;
        lo++;
      }
    }
  }

  static void nSum(const std::vector<int>& nums,
                   const int K,
                   std::vector<std::vector<int>>& out,
                   const long target,
                   const int start,
                   const int level)
  {
    const int N = nums.size();
    if (start == N)
      return;

    long long average_value = target / level;

    if (average_value < nums[start] || nums.back() < average_value)
      return;

    if (level == 2) {
      twoSum(nums, K, out, target, start);
      return;
    }

    for (int i = start; i < N - level + 1; ++i) {
      if (i != start && nums[i - 1] == nums[i])
        continue;

      auto preSize = out.size();
      nSum(nums, K, out, target - nums[i], i + 1, level - 1);
      for (; preSize < out.size(); preSize++) {
        out[preSize][K - level] = nums[i];
      }
    }
  }

public:
  static std::vector<std::vector<int>> fourSum(std::vector<int>& nums, const int target)
  {
    std::ranges::sort(nums);
    std::vector<std::vector<int>> ans;
    nSum(nums, 4, ans, target, 0, 4);
    return ans;
  }
};

int
main()
{
  return 0;
}
