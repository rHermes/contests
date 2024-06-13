#include <array>
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
  static int minFlips(const std::vector<std::vector<int>>& mat)
  {
    constexpr int MAXN = 3;
    std::array<bool, MAXN * MAXN*(MAXN * MAXN + 1)> trans;

    const int ROWS = mat.size();
    const int COLS = mat[0].size();

    const int NM = ROWS * COLS;
    // one more, because we want, to also add the variable.
    const int NMA = NM + 1;
    std::fill_n(trans.begin(), NM * NMA, false);

    // Initialize the transition matrix.
    bool allZero = true;
    for (int y = 0; y < ROWS; y++) {
      for (int x = 0; x < COLS; x++) {
        const int offset = (y * COLS + x) * NMA;

        trans[offset + (y * COLS + x)] = 1;
        trans[offset + NM] = mat[y][x];

        if (mat[y][x])
          allZero = false;

        if (0 < x) {
          trans[offset + (y * COLS + x - 1)] = 1;
        }
        if (x < COLS - 1) {
          trans[offset + (y * COLS + x + 1)] = 1;
        }
        if (0 < y) {
          trans[offset + ((y - 1) * COLS + x)] = 1;
        }
        if (y < ROWS - 1) {
          trans[offset + ((y + 1) * COLS + x)] = 1;
        }
      }
    }

    // this is the lights are zero then, we are done.
    if (allZero)
      return 0;

    // we double check to see if there is a single button we
    // can press to fix this.
    for (int row = 0; row < NM; row++) {
      int found = true;
      for (int i = 0; i < NM; i++) {
        if (trans[row * NMA + i] != trans[i * NMA + NM]) {
          found = false;
          break;
        }
      }
      if (found)
        return 1;
    }

    const auto swapRows = [&](const int a, const int b) {
      if (a == b)
        return;

      int offsetA = a * NMA;
      int offsetB = b * NMA;
      std::swap_ranges(trans.begin() + offsetA, trans.begin() + offsetA + NMA, trans.begin() + offsetB);
    };

    const auto addRows = [&](const int src, const int dst) {
      int offsetA = src * NMA;
      int offsetB = dst * NMA;
      for (int i = 0; i < NMA; i++) {
        trans[offsetB + i] ^= trans[offsetA + i];
      }
    };

    // We will do something called graham smith normalization.
    int pivCol = 0;
    int pivRow = 0;

    while (pivCol < NMA && pivRow < NM) {
      bool found = false;
      for (int i = pivRow; i < NM; i++) {
        if (trans[i * NMA + pivCol]) {
          found = true;
          swapRows(pivRow, i);
          break;
        }
      }

      if (!found) {
        pivCol++;
        continue;
      }

      for (int i = 0; i < NM; i++) {
        if (i == pivRow)
          continue;

        if (trans[i * NMA + pivCol]) {
          addRows(pivRow, i);
        }
      }

      pivCol++;
      pivRow++;
    }

    if (pivCol != NM) {
      int ans = 0;
      for (int i = pivRow - 1; i < NM; i++) {
        ans += trans[i * NMA + NM];
      }
      if (ans)
        return -1;
    } else {
      int ans = 0;
      for (int i = 0; i < NM; i++) {
        ans += trans[i * NMA + NM];
      }
      return ans;
    }

    return 0;
  }
};
