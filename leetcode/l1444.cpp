#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

constexpr int MODN = 1000000007;

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
private:
  std::array<std::int16_t, 51 * 51> PSA;
  std::array<int, 51 * 51 * 10> MEMO;

  std::size_t ROWS;
  std::size_t COLS;
  std::size_t PROWS;
  std::size_t PCOLS;

  std::size_t K;

  int solve(int y, int x, int k)
  {
    const auto totalLeft = PSA[PCOLS * y + x];

    if (totalLeft <= k) {
      return 0;
    }

    if (k == 0) {
      return 1;
    }

    const std::size_t key = y * (COLS * K) + x * K + k;
    if (MEMO[key] != -1)
      return MEMO[key];

    std::int64_t ans = 0;
    for (std::size_t ny = y + 1; ny < ROWS; ny++) {
      const auto leftAbove = totalLeft - PSA[ny * PCOLS + x];

      if (leftAbove <= 0)
        continue;

      if (leftAbove == totalLeft)
        break;

      ans = (ans + solve(ny, x, k - 1)) % MODN;
    }

    for (std::size_t nx = x + 1; nx < COLS; nx++) {
      const auto leftLeft = totalLeft - PSA[y * PCOLS + nx];

      if (leftLeft <= 0)
        continue;

      if (leftLeft == totalLeft)
        break;

      ans = (ans + solve(y, nx, k - 1)) % MODN;
    }

    MEMO[key] = ans;
    return ans;
  };

public:
  int ways(const std::vector<std::string>& pizza, int k)
  {
    ROWS = pizza.size();
    COLS = pizza[0].size();
    PCOLS = COLS + 1;
    PROWS = ROWS + 1;

    K = k;

    // We need to make sure that the PSA edges are filled in before we
    // start, as we might be reusing the cache from a previous run.
    for (std::size_t col = 0; col < COLS; col++) {
      PSA[ROWS * PCOLS + col] = 0;
    }
    for (std::size_t row = 0; row < ROWS; row++) {
      PSA[row * PCOLS + COLS] = 0;
    }

    // Ok, we flip the script a little here. We are going to build a PSA
    // where we are recording the sum to the lower right corner. This fit's
    // a lot better with the task.
    for (int row = ROWS - 1; 0 <= row; row--) {
      for (int col = COLS - 1; 0 <= col; col--) {
        PSA[row * PCOLS + col] = (pizza[row][col] == 'A') + PSA[(row + 1) * PCOLS + col] + PSA[row * PCOLS + col + 1] -
                                 PSA[(row + 1) * PCOLS + col + 1];
      }
    }

    std::fill_n(MEMO.begin(), ROWS * COLS * K, -1);
    return solve(0, 0, k - 1);
  }
};
