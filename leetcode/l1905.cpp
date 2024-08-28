#include <iostream>
#include <memory>
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
  static int countSubIslands(const std::vector<std::vector<int>>& grid1, const std::vector<std::vector<int>>& grid2)
  {
    const int ROWS = grid1.size() + 2;
    const int COLS = grid1[0].size() + 2;

    // We create a border around the island, to avoid branches in the loop below.
    auto seen = std::make_unique_for_overwrite<unsigned char[]>(ROWS * COLS);
    for (int x = 0; x < COLS; x++) {
      seen[0 * COLS + x] = 0;
      seen[(ROWS - 1) * COLS + x] = 0;
    }
    for (int y = 1; y < ROWS - 1; y++) {
      seen[y * COLS + 0] = 0;
      seen[y * COLS + (COLS - 1)] = 0;
    }

    for (int i = 1; i < ROWS - 1; i++) {
      for (int j = 1; j < COLS - 1; j++) {
        seen[i * COLS + j] = grid1[i - 1][j - 1];
        seen[i * COLS + j] <<= 1;
        seen[i * COLS + j] |= grid2[i - 1][j - 1];
      }
    }

    const auto testAndClear = [&](const auto key) {
      if (!(seen[key] & 1))
        return false;

      seen[key] ^= 1;
      return true;
    };

    auto Q = std::make_unique_for_overwrite<int[]>(COLS * ROWS);
    int Qidx = 0;

    const auto tryAdd = [&](const auto key) {
      if (testAndClear(key)) {
        Q[Qidx++] = key;
      }
    };

    int ans = 0;
    for (int i = 1; i < ROWS - 1; i++) {
      for (int j = 1; j < COLS - 1; j++) {
        const auto firstKey = i * COLS + j;
        if (!testAndClear(firstKey))
          continue;

        bool goodSub = true;

        Q[Qidx++] = firstKey;

        while (0 < Qidx) {
          const auto curKey = Q[--Qidx];

          goodSub = goodSub && seen[curKey] & 2;

          tryAdd(curKey - COLS); // Up
          tryAdd(curKey + COLS); // Down
          tryAdd(curKey - 1);    // Left
          tryAdd(curKey + 1);    // Right
        }

        ans += goodSub;
      }
    }

    return ans;
  }
};
