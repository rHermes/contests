#include <cstdint>
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
  // Return the number of subarrays with sum <= target
  static constexpr std::pair<int, std::int64_t> countAndSum(const std::vector<int>& nums, const int N, const int target)
  {
    int count = 0;
    std::int64_t currentSum = 0;
    std::int64_t totalSum = 0;
    std::int64_t windowSum = 0;

    int l = 0;
    for (int r = 0; r < N; r++) {
      currentSum += nums[r];

      // well, how many arrays are there to make of [l, r], that include
      // r? the answer is (r-l+1), so whatever the total sum is, we just
      // added r to it that many times.
      windowSum += nums[r] * (r - l + 1);

      while (target < currentSum) {
        // ok, this fell out of the view, so we remove this from the
        // window pool
        windowSum -= currentSum;
        currentSum -= nums[l++];
      }
      // All arrays with [l, r], from l,l+1, to r, has a smaller sum, we
      // so count them together.
      count += r - l + 1;
      totalSum += windowSum;
    }

    // ok, now we have the count, what about their sum?
    return { count, totalSum };
  }

  // Return the number of subarrays with sum <= target
  static constexpr int countUnder(const std::vector<int>& nums, const int N, const int target)
  {
    int count = 0;
    int currentSum = 0;

    int l = 0;
    for (int r = 0; r < N; r++) {
      currentSum += nums[r];

      while (target < currentSum) {
        currentSum -= nums[l++];
      }
      count += r - l + 1;
    }

    // ok, now we have the count, what about their sum?
    return count;
  }

public:
  static constexpr int rangeSum(const std::vector<int>& nums, const int n, const int left, const int right)
  {
    const int minSum = 1;
    const int maxSum = 100 * n;

    const auto sumOfFirstK = [&](const int target) -> std::int64_t {
      int left = minSum;
      int right = maxSum;

      while (left <= right) {
        const auto mid = std::midpoint(left, right);
        const auto count = countUnder(nums, n, mid);

        if (target <= count) {
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      }

      const auto [count, sum] = countAndSum(nums, n, left);

      // There can be many arrays with the same sum, so we reduce here to
      // get the sum from the first one.
      return sum - left * (count - target);
    };

    constexpr int MODN = 1000000007;
    const auto rightSum = sumOfFirstK(right);
    const auto leftSum = sumOfFirstK(left - 1);
    return (rightSum - leftSum) % MODN;
  }
};
