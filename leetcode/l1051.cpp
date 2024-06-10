#include <algorithm>
#include <vector>
class Solution
{
public:
  static int heightChecker(const std::vector<int>& heights)
  {
    auto tmp = heights;
    std::ranges::sort(tmp);
    int ans = 0;
    for (std::size_t i = 0; i < heights.size(); i++)
      ans += heights[i] != tmp[i];

    return ans;
  }
};
