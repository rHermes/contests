#include <cstdint>
#include <vector>

class Solution
{
public:
  bool possibleToStamp(std::vector<std::vector<int>>& grid, int stampHeight, int stampWidth)
  {

    const auto SH = static_cast<std::size_t>(stampHeight);
    const auto SW = static_cast<std::size_t>(stampWidth);

    // this is rather easy thenl. We can convert this to a 2d prefix sum
    // array.
    const auto R = grid.size();
    const auto C = grid.front().size();

    if (R < SH || C < SW) {
      // we need to check if every square is good.
      for (const auto& row : grid)
        for (const auto& c : row)
          if (c == 0)
            return false;

      return true;
    }

    std::vector<std::vector<std::int32_t>> psa(R + 1, std::vector<std::int32_t>(C + 1));
    for (std::size_t r = 1; r <= R; r++) {
      for (std::size_t c = 1; c <= C; c++) {
        psa[r][c] = psa[r - 1][c] + psa[r][c - 1] - psa[r - 1][c - 1] + grid[r - 1][c - 1];
      }
    }

    auto taken = [&psa](std::size_t tr, std::size_t tc, std::size_t br, std::size_t bc) {
      const auto sum = psa[br][bc] + psa[tr - 1][tc - 1] - psa[tr - 1][bc] - psa[br][tc - 1];

      return sum != 0;
    };

    // now we mark the grid.

    // This is the low watermark for writing. We can use this to avoid
    // writing unneccarily.
    std::size_t minR = 1;
    for (std::size_t r = 1; r <= R - SH + 1; r++) {
      std::size_t minC = 1;

      minR = std::max(minR, r);

      // std::cout << "We are working on row: " << r << std::endl;

      // We check if we can do a small skip, by testing the range of the
      // stencil
      if (!taken(r, 1, r + SH - 1, C)) {
        // std::cout << "BIG SKIP" << std::endl;
        for (std::size_t rm = minR - 1; rm < r - 1 + SH; rm++) {
          for (std::size_t cm = 0; cm < C; cm++) {
            grid[rm][cm] = 1;
          }
        }

        minR = std::max(minR, r + SH - 1);
        continue;
      }

      for (std::size_t c = 1; c <= C - SW + 1; c++) {
        auto hit = taken(r, c, r + SH - 1, c + SW - 1);
        if (hit) {
          continue;
        }

        minC = std::max(minC, c);

        for (std::size_t rm = minR - 1; rm < r - 1 + SH; rm++) {
          for (std::size_t cm = minC - 1; cm < c - 1 + SW; cm++) {
            grid[rm][cm] = 1;
          }
        }
        minC = c - 1 + SW;
      }
    }

    // verify that we painted all rows.
    for (const auto& row : grid)
      for (const auto& c : row)
        if (c == 0)
          return false;

    return true;
  }
};
