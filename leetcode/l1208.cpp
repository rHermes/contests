#include <algorithm>
#include <iostream>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static constexpr int equalSubstring(const std::string& s, const std::string& t, int maxCost)
  {
    int l = 0;
    int curCost = 0;
    int ans = 0;
    const int N = s.size();
    for (int r = 0; r < N; r++) {
      curCost += std::abs(s[r] - t[r]);

      while (maxCost < curCost) {
        curCost -= std::abs(s[l] - t[l]);
        l++;
      }

      ans = std::max(ans, r - l + 1);
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
