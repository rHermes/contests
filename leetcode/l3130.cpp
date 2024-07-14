#include <cstdint>
#include <vector>

class Solution
{
  static constexpr int MODN = 1000000007;

public:
  static int numberOfStableArrays(const int zero, const int one, const int limit)
  {
    const int ROW = std::max(zero, one) + 1;
    const int PROW = ROW + 1;
    std::vector<int> psa(PROW * PROW, 0);

    auto getPsa = [&](int o, int x) -> int& { return psa[(o + 1) * PROW + x + 1]; };

    auto getPsaSum = [&](int hiO, int hiX, int loO, int loX) -> int {
      std::int64_t tmp = getPsa(hiO, hiX);

      tmp -= getPsa(loO - 1, hiX);
      tmp -= getPsa(hiO, loX - 1);
      tmp += getPsa(loO - 1, loX - 1);

      return tmp % MODN;
    };

    auto setPsaSum = [&](int os, int xs, const int extra) {
      std::int64_t tmp = getPsa(os, xs);

      tmp += getPsa(os - 1, xs);
      tmp += getPsa(os, xs - 1);
      tmp -= getPsa(os - 1, xs - 1);
      tmp += extra;

      getPsa(os, xs) = tmp % MODN;
    };

    getPsa(0, 0) = 1;

    // Now, let's start building here.
    for (int os = 0; os < ROW; os++) {
      for (int xs = 0; xs < ROW; xs++) {
        if (os == 0 && xs == 0) {
          continue;
        }

        // lower limit
        int loX = std::max(0, xs - limit);
        int loO = std::max(0, os - limit);

        int extra = 0;
        if (loX < xs && loO < os) {
          extra = getPsaSum(os - 1, xs - 1, loO, loX);
        }

        setPsaSum(os, xs, extra);
      }
    }

    int ans = 0;

    {
      // zero = x, one = o
      int loO = std::max(0, one - limit);
      ans += getPsaSum(one, zero, loO, zero);
    }

    {
      // zero = o, one = x
      int loO = std::max(0, zero - limit);
      ans += getPsaSum(zero, one, loO, one);
    }

    ans %= MODN;
    return (ans + MODN) % MODN;
  }
};
