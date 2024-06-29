#include <cstdint>

class Solution
{
public:
  static constexpr int countOrders(const int n)
  {
    if (n == 1)
      return 1;

    constexpr std::int64_t MODN = 1000000007;

    std::int64_t ans = 1;
    for (int i = 0; i < n; i++) {
      // This is taken from that there are 2*spotsLeft really, and all pairs are:
      // (2*spotsLeft) * (2*spotsLeft - 1), and half of those are going to be illegal,
      // so we divide by two. If you multiply this out, you are able to avoid a division
      //
      const std::int64_t spotsLeft = (n - i);
      const std::int64_t validPlacements = spotsLeft * (2 * spotsLeft - 1);

      ans = (ans * validPlacements) % MODN;
    }

    return ans;
  }
};
