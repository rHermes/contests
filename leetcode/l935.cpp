#include <array>
#include <cstdint>
#include <numeric>

class Solution
{
  using AT = std::array<std::int64_t, 81>;
  static constexpr std::int64_t MODN = 1000000007;

public:
  static void matMult(const AT& a, const AT& b, AT& out)
  {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        out[i * 9 + j] = 0;
        for (int k = 0; k < 9; k++) {
          out[i * 9 + j] += a[i * 9 + k] * b[k * 9 + j];
          out[i * 9 + j] %= MODN;
        }
      }
    }
  }

  static int knightDialer(int n)
  {
    if (n == 1)
      return 10;
    constexpr AT base{
      //  1  2  3  4  6  7  8  9  0
      0, 0, 0, 0, 1, 0, 1, 0, 0, // 1
      0, 0, 0, 0, 0, 1, 0, 1, 0, // 2
      0, 0, 0, 1, 0, 0, 1, 0, 0, // 3
      0, 0, 1, 0, 0, 0, 0, 1, 1, // 4
      1, 0, 0, 0, 0, 1, 0, 0, 1, // 6
      0, 1, 0, 0, 1, 0, 0, 0, 0, // 7
      1, 0, 1, 0, 0, 0, 0, 0, 0, // 8
      0, 1, 0, 1, 0, 0, 0, 0, 0, // 9
      0, 0, 0, 1, 1, 0, 0, 0, 0, // 0
    };

    AT powMat{};
    for (int i = 0; i < 9; i++) {
      powMat[i * 9 + i] = 1;
    }

    AT exper = base;

    AT temp{};
    n--;
    while (n > 0) {
      if (n & 1) {
        matMult(powMat, exper, temp);
        powMat = temp;
      }

      matMult(exper, exper, temp);
      exper = temp;
      n >>= 1;
    }

    std::int64_t ans = std::reduce(powMat.begin(), powMat.end(), static_cast<std::int64_t>(0));
    return (ans % MODN);
  }
};
