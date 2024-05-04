#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  static int smallestRangeII(std::vector<int> &nums, int k) {
    if (nums.size() <= 1)
      return 0;

    std::ranges::sort(nums);
    int maxAns = nums.back() - nums.front();

    // if the delta is too big, we are never going to get any better.
    if (k <= 0 || maxAns <= k) {
      return maxAns;
    }

    // Ok, so the intuition is this: We are essentially going to choose a split point,
    // where everything to the left, we are going to push up and everything to the right,
    // we are going to push down.
    //
    // This means that we just gotta find the "minimum", "maximum" value for this.

    // we just gotta keep track of a few things then. at point I, we know the high point on the
    // right will be, it will be:
    const int maxRight = nums.back() - k;

    // on the left, the min will be.
    const int minLeft = nums.front() + k;

    // Now, we can compare that two our current

    for (std::size_t i = 1; i < nums.size(); i++) {
      const int prevUp = nums[i - 1] + k;
      const int thisDown = nums[i] - k;

      const int maxNow = std::max(prevUp, maxRight);
      const int minNow = std::min(thisDown, minLeft);

      maxAns = std::min(maxAns, maxNow - minNow);
    }

    return maxAns;
  }
};

static const auto __optimize__ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();
