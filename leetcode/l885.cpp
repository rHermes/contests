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
  static constexpr std::vector<std::vector<int>> spiralMatrixIII(const int rows,
                                                                 const int cols,
                                                                 const int rStart,
                                                                 const int cStart)
  {
    const int N = rows * cols;

    std::vector<std::vector<int>> out(N);
    int outIdx = 0;

    const auto addOutput = [&](const int y, const int x) -> bool {
      out[outIdx++] = { y, x };
      return outIdx == N;
    };

    int pX = cStart;
    int pY = rStart;

    if (addOutput(pY, pX))
      return out;

    int width = 1;
    while (true) {
      // Going right
      const int destX = pX + width;
      if (0 <= pY) {
        const int maxX = std::min(cols - 1, destX);
        for (int x = std::max(0, pX + 1); x <= maxX; x++) {
          if (addOutput(pY, x))
            return out;
        }
      }
      pX = destX;

      // Going down
      const int destY = pY + width;
      if (pX < cols) {
        const int maxY = std::min(rows - 1, destY);
        for (int y = std::max(0, pY + 1); y <= maxY; y++) {
          if (addOutput(y, pX))
            return out;
        }
      }
      pY = destY;

      // Going left
      const int destX2 = pX - width - 1;
      if (pY < rows) {
        const int minX = std::max(0, destX2);
        for (int x = std::min(cols - 1, pX - 1); minX <= x; x--) {
          if (addOutput(pY, x))
            return out;
        }
      }
      pX = destX2;

      // Going up
      const int destY2 = pY - width - 1;
      if (0 <= pX) {
        const int minY = std::max(0, destY2);
        for (int y = std::min(rows - 1, pY - 1); minY <= y; y--) {
          if (addOutput(y, pX))
            return out;
        }
      }
      pY = destY2;

      // We increase the width.
      width += 2;
    }
  }
};
