#include <bitset>
#include <vector>

class Solution
{
public:
  int findMaxK(std::vector<int>& nums)
  {
    constexpr std::size_t MID = 1000;
    std::bitset<MID + 1> pos;
    std::bitset<MID + 1> neg;

    int ans = -1;
    for (const auto& num : nums) {
      if (0 <= num) {
        pos[num] = true;

        // we check if the positive is there
        if (neg[num] && ans < num) {
          ans = num;
        }
      } else {
        const auto flip = -num;
        neg[flip] = true;

        if (pos[flip] && ans < (flip)) {
          ans = flip;
        }
      }
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
