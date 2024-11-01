#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  int longestSquareStreak(std::vector<int>& nums)
  {
    // so we are actually just going to to be looking at the squares.
    // I guess we can techincally sort them? But we don't need to I think.
    std::ranges::sort(nums);
    std::unordered_map<long, int> seen;

    int ans = -1;
    for (const auto x : nums) {
      if (auto it = seen.find(x); it != seen.end()) {
        ans = std::max(ans, 1 + it->second);
        seen.emplace(static_cast<long>(x) * x, 1 + it->second);
      } else {
        seen.emplace(static_cast<long>(x) * x, 1);
      }
    }

    return ans;
  }
};
