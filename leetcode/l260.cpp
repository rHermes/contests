#include <bit>
#include <vector>

class Solution
{
public:
  static std::vector<int> singleNumber(const std::vector<int>& nums)
  {
    // ok, I can do an xor, that will bring out their xor score atleast.
    int xo = 0;
    for (auto x : nums)
      xo ^= x;

    // now we have a bit which we can partion on.
    int firstBit = std::countr_zero(static_cast<unsigned int>(xo));
    int mask = 1 << firstBit;

    int on = 0;
    for (auto x : nums)
      if (x & mask)
        on ^= x;

    return { on, xo ^ on };
  }
};

int
main()
{
  return 0;
}
