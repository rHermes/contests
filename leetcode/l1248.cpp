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
  static int numberOfSubarrays(const std::vector<int>& nums, int k)
  {
    const int N = nums.size();
    int ans = 0;

    std::vector<int> odds(k + 1);
    int oddsPos = 0;
    odds[k] = -1;

    // First let's fill up the stack.
    int r;
    for (r = 0; r < N && oddsPos < k; r++) {
      if (nums[r] % 2 != 0) {
        odds[oddsPos++] = r;
      }
    }

    // now if oddsPos != k, we know the answer is 0
    if (oddsPos != k) {
      return 0;
    }

    // now we are in a position to do some damage here.
    for (; r < N; r++) {
      if (nums[r] % 2 == 0)
        continue;

      // ok, so now we are going to replace one of them.
      // but first we now need to know, how many subarrays are with the current configuration.
      int toTheRight = r - odds[(oddsPos - 1 + (k + 1)) % (k + 1)];
      int toTheLeft = odds[(oddsPos + 1) % (k + 1)] - odds[oddsPos];

      /* std::cout << "I have " << toTheRight << " and " << toTheLeft << "\n"; */

      ans += (toTheLeft * toTheRight);

      odds[oddsPos++] = r;
      oddsPos %= k + 1;
    }

    // Finally we do the final setup
    int toTheRight = N - odds[(oddsPos - 1 + (k + 1)) % (k + 1)];
    int toTheLeft = odds[(oddsPos + 1) % (k + 1)] - odds[oddsPos];
    ans += (toTheRight * toTheLeft);

    return ans;
  }
};
