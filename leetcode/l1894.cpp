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
  static constexpr int chalkReplacer(const std::vector<int>& chalk, int k)
  {
    int totalSum = 0;
    const int N = chalk.size();

    for (int i = 0; i < N; i++) {
      totalSum += chalk[i];
      k -= chalk[i];
      if (k < 0) {
        return i;
      }
    }

    k %= totalSum;
    for (int i = 0; i < N; i++) {
      k -= chalk[i];
      if (k < 0) {
        return i;
      }
    }

    return -1;
  }
};
