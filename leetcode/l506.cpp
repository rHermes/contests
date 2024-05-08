#include <algorithm>
#include <iostream>
#include <numeric>
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
  static std::vector<std::string> findRelativeRanks(const std::vector<int>& score)
  {
    std::vector<int> pos(score.size());
    std::iota(pos.begin(), pos.end(), 0);

    std::sort(pos.begin(), pos.end(), [&](const int i, const int j) { return score[j] < score[i]; });

    std::vector<std::string> ans(score.size());
    ans.reserve(score.size());
    for (std::size_t i = 0; i < score.size(); i++) {
      switch (i) {
        case 0:
          ans[pos[i]] = "Gold Medal";
          break;
        case 1:
          ans[pos[i]] = "Silver Medal";
          break;
        case 2:
          ans[pos[i]] = "Bronze Medal";
          break;

        default:
          ans[pos[i]] = std::to_string(i + 1);
          break;
      }
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
