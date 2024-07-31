#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int constexpr minimumDeletions(const std::string& s)
  {
    int ans = 0;
    int countB = 0;
    for (const auto c : s) {
      if (c == 'b') {
        countB++;
      } else {
        ans = std::min(ans + 1, countB);
      }
    }

    return ans;
  }
};
