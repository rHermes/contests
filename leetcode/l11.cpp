#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
public:
  int maxArea(std::vector<int>& height)
  {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::size_t L = 0;
    std::size_t R = height.size() - 1;

    int ans = static_cast<int>(R - L) * std::min(height[L], height[R]);

    while (L + 1 < R) {
      if (height[L] < height[R])
        L++;
      else
        R--;

      ans = std::max(ans, static_cast<int>(R - L) * std::min(height[L], height[R]));
    }
    return ans;
  }
};

int
main()
{
  return 0;
}
