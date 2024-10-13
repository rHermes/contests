#include <iostream>
#include <limits>
#include <queue>
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
  std::vector<int> smallestRange(std::vector<std::vector<int>>& nums)
  {
    const int N = nums.size();

    // ok, so the idea we are working off here, is that we essentially can
    // ok, this is the key insight. If we select one element from each list,
    // then we can always create a range which covers all. Each range will
    // then also always include at least one element from each list.
    int maxElem = std::numeric_limits<int>::lowest();

    // val, li, li idx
    using T = std::tuple<int, int, int>;
    std::priority_queue<T, std::vector<T>, std::ranges::greater> Q;

    int rangeStart = 0;
    int rangeEnd = std::numeric_limits<int>::max();

    for (int i = 0; i < N; i++) {
      Q.emplace(nums[i][0], i, 0);
      maxElem = std::max(maxElem, nums[i][0]);
    }

    while (true) {
      // Now we pick the smallest one.
      const auto [val, li, idx] = Q.top();
      Q.pop();

      if (maxElem - val < (rangeEnd - rangeStart)) {
        rangeStart = val;
        rangeEnd = maxElem;
      }

      if (idx + 1 == static_cast<int>(nums[li].size())) {
        return { rangeStart, rangeEnd };
      }

      Q.emplace(nums[li][idx + 1], li, idx + 1);

      maxElem = std::max(maxElem, nums[li][idx + 1]);
    }
  }
};
