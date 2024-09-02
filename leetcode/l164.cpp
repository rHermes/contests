#include <algorithm>
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
  static constexpr int maximumGap(const std::vector<int>& nums)
  {
    const int N = nums.size();

    auto [mmin, mmax] = std::ranges::minmax(nums);
    const int inputSpan = mmax - mmin;
    if (inputSpan < 2) {
      return inputSpan;
    }

    // Now here comes the cool part. We divide these numbers into n-1 groups. Now the sum of all differences inside of
    // the array, would sum up to mmax-mmin. Inside of each bucket the max span can max be (mmax-mmin)/(n-1). Since
    // there are n numbers, but only n-1 buckets, at least two buckets has to be occupied. This means that at least one
    // of gaps will be across buckets. All these gaps cannot be smaller than (mmax-mmin)/(n-1) as that would mean that
    // the total would be too small. This means that either it's the answer or it's larger.
    const int bucketSize = std::max(1, (inputSpan) / (N - 1));

    std::vector<std::pair<int, int>> buckets(N, { std::numeric_limits<int>::max(), std::numeric_limits<int>::min() });

    for (const auto x : nums) {
      const auto bucketNum = std::min(N - 1, (x - mmin) / bucketSize);
      buckets[bucketNum].first = std::min(buckets[bucketNum].first, x);
      buckets[bucketNum].second = std::max(buckets[bucketNum].second, x);
    }

    // ok, we just compare the buckets.
    int ans = std::numeric_limits<int>::min();
    int prevHigh = buckets[0].second;
    for (int i = 1; i < N; i++) {
      const auto& [bl, bh] = buckets[i];
      if (bh < bl)
        continue;

      ans = std::max(ans, bl - prevHigh);
      prevHigh = bh;
    }

    return ans;
  }
};
