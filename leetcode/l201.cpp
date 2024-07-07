#include <bit>
#include <cstdint>

class Solution
{
public:
  static constexpr int rangeBitwiseAnd(int left, int right)
  {
    // We need to find the shared prefix.
    std::uint32_t c = left ^ right;
    std::uint32_t sharedPre = std::countl_zero(c);

    // We now treat them as 64 bit numbers, to allow shifts of 32.
    std::uint64_t r = right;
    r >>= (32 - sharedPre);
    r <<= (32 - sharedPre);
    return r;
  }
};
