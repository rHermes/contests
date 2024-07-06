#include <iostream>
#include <string>
#include <utility>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

/**
 * The idea here is to split the strings into groups who share the same prefix
 * and just operate within these. This let's us work on just the elements which
 * still require sorting.
 */

class Solution
{
public:
  static int minDeletionSize(const std::vector<std::string>& strs)
  {
    const int N = strs.size();
    const int SN = strs[0].size();

    std::vector<std::pair<int, int>> group = { { 0, N } };
    std::vector<std::pair<int, int>> nextGroup;

    group.reserve(26);
    nextGroup.reserve(26);

    int ans = 0;
    for (int col = 0; col < SN; col++) {
      nextGroup.clear();

      bool allGood = true;
      for (const auto& [start, end] : group) {

        if (end - start <= 1) {
          continue;
        }

        bool good = true;
        int lastSplit = start;
        for (int row = start + 1; row < end; row++) {
          const auto ac = strs[row - 1][col];
          const auto bc = strs[row][col];

          if (bc < ac) {
            good = false;
            break;
          } else if (ac < bc) {
            if (1 < row - lastSplit)
              nextGroup.emplace_back(lastSplit, row);
            lastSplit = row;
          }
        }

        if (good) {
          if (1 < end - lastSplit)
            nextGroup.emplace_back(lastSplit, end);
        } else {
          allGood = false;
          break;
        }
      }

      if (allGood) {
        if (nextGroup.empty())
          break;

        group = nextGroup;
      } else {
        ans++;
      }
    }

    return ans;
  }
};
