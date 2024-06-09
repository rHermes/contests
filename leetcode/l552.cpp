#include <array>
#include <cstdint>
#include <numeric>

class Solution
{
  // To prevent overflow issues, and to minimize number of MODN operations
  using T = std::int64_t;

  // Matix type
  using AT = std::array<T, 7 * 7>;

  // row vector type
  using BT = std::array<T, 7>;

  static constexpr T MODN = 1000000007;

  static constexpr void matrixMult(const AT& a, const AT& b, AT& out)
  {
    for (int row = 0; row < 7; row++) {
      for (int col = 0; col < 7; col++) {
        out[row * 7 + col] = 0;
        for (int i = 0; i < 7; i++) {
          out[row * 7 + col] += (a[row * 7 + i] * b[i * 7 + col]) % MODN;
        }
        out[row * 7 + col] %= MODN;
      }
    }
  }

  static constexpr void matrixVecMult(const AT& a, const BT& b, BT& out)
  {
    for (int row = 0; row < 7; row++) {
      out[row] = 0;
      for (int i = 0; i < 7; i++) {
        out[row] += (a[row * 7 + i] * b[i]) % MODN;
      }
      out[row] %= MODN;
    }
  }

public:
  static constexpr int checkRecord(int n)
  {
    // clang-format off
        // Nx = Not absent yet, last letter was x
        // Ax = Absent before , last letter was x
        // Cols: NP, NL, NLL, AP, AL, ALL, AA
        AT mat = {
            1, 1, 1, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 1,
            0, 0, 0, 1, 0, 0, 1,
            0, 0, 0, 0, 1, 0, 0,
            1, 1, 1, 0, 0, 0, 0
        };


        AT raised = {
            1, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 0, 1,
        };
    // clang-format on

    AT tmp;

    // Ok, now we are going to do exponantiation by squaring here.
    --n;
    while (0 < n) {
      if (n & 1) {
        matrixMult(mat, raised, tmp);
        raised = tmp;
      }

      matrixMult(mat, mat, tmp);
      mat = tmp;

      n >>= 1;
    }

    BT init = { 1, 1, 0, 0, 0, 0, 1 };
    BT ans;
    matrixVecMult(raised, init, ans);

    return std::reduce(ans.begin(), ans.end(), static_cast<T>(0)) % MODN;
  }
};
