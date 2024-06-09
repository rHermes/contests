#include <iostream>
#include <unordered_set>
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
  static int longestConsecutive(const std::vector<int>& nums)
  {
    if (nums.empty())
      return 0;

    std::unordered_set<int> lookup;
    for (const auto x : nums) {
      lookup.emplace(x);
    }

    int ans = 1;
    for (auto x : lookup) {
      if (lookup.contains(x - 1))
        continue;

      int i = 1;
      while (lookup.contains(x + i))
        i++;

      ans = std::max(ans, i);
    }

    return ans;
  }
};
