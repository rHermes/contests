#include <bitset>
#include <cstdint>
#include <vector>

class Solution
{
public:
  bool canCross(std::vector<int>& stones)
  {
    if (stones[1] != 1)
      return false;

    if (stones.size() == 2)
      return true;

    // We can tackle this from the back.
    // landing on the last set of stones,
    std::vector<std::uint64_t> diffs(stones.size() - 1);
    for (std::size_t i = 0; i < stones.size() - 1; i++)
      diffs[i] = static_cast<std::uint64_t>(stones[i + 1] - stones[i]);

    // Ok, now we create an array here.
    // Max speed we can get is 2001 legitematly, but we put a bit higher here
    // just to make things easier. We use 2048 because it's the next multuple of
    // 64 after 2006
    std::vector<std::bitset<2006>> dp(diffs.size() + 1);

    // As long as we make it there, we are good.
    dp.back().set();

    for (std::size_t i = diffs.size(); 0 < i; i--) {
      const std::size_t ii = i - 1;

      // Ok, so now. We just check for each value going forward
      // if they are true, and we add a bit of suspense.
      std::size_t sum = 0;
      for (std::size_t j = ii; j < diffs.size(); j++) {
        sum += diffs[j];

        if (2000 < sum)
          break;

        const auto value = dp[j + 1][sum];
        if (!value)
          continue;

        dp[ii][sum - 1] = true;
        dp[ii][sum] = true;
        dp[ii][sum + 1] = true;
      }
    }
    return dp[0][0];
  }
};

int
main()
{
  return 0;
}
