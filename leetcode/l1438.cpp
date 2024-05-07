#include <deque>
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
  static int longestSubarray(const std::vector<int>& nums, const int limit)
  {
    // We keep track of the minimum and maximum elements in two queues.
    // A multiset could also work, but has more overhead.
    std::deque<int> mind;
    std::deque<int> maxd;

    int ans = 0;

    std::size_t l = 0;
    for (std::size_t r = 0; r < nums.size(); r++) {
      const auto n = nums[r];

      // The front element here, is the largest element.
      while (!maxd.empty() && maxd.back() < n)
	maxd.pop_back();
      maxd.push_back(n);

      // The front element here, is the smallest element.
      while (!mind.empty() && n < mind.back())
	mind.pop_back();
      mind.push_back(n);

      while (limit < (maxd.front() - mind.front())) {
	const auto out = nums[l++];

	if (maxd.front() == out)
	  maxd.pop_front();

	if (mind.front() == out)
	  mind.pop_front();
      }

      ans = std::max(ans, static_cast<int>(r - l + 1));
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
