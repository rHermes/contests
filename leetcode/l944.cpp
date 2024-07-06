#include <iostream>
#include <string>
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
  static constexpr int minDeletionSize(const std::vector<std::string>& strs)
  {
    const int N = strs.size();
    const int SN = strs[0].size();

    int ans = 0;
    for (int col = 0; col < SN; col++) {
      for (int row = 1; row < N; row++) {
        if (strs[row][col] < strs[row - 1][col]) {
          ans++;
          break;
        }
      }
    }

    return ans;
  }
};
