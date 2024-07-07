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
  static int minDeletionSize(const std::vector<std::string>& strs)
  {
    // The trick in this question is to reinterpret it as a longest
    // increasing subsequence problem, but without a total ordering. This
    // gives the good old SN * SN * W time requirement.
    const int SN = strs.front().size();

    const auto lessThan = [&](const int a, const int b) -> bool {
      for (const auto& word : strs) {
        if (word[b] < word[a])
          return false;
      }
      return true;
    };

    std::vector<int> d(SN, 1);
    int ans = 1;
    for (int i = 0; i < SN; i++) {
      for (int j = 0; j < i; j++) {
        if (lessThan(j, i)) {
          d[i] = std::max(d[i], d[j] + 1);
          ans = std::max(ans, d[i]);
        }
      }
    }

    return SN - ans;
  }
};
