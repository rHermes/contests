#include <bit>
#include <cstdint>

class Solution
{
public:
  static constexpr int findComplement(int num)
  {
    const auto premask = std::countl_zero(static_cast<std::uint32_t>(num));
    const std::uint32_t wow = 1 << (32 - premask);
    const std::uint32_t mask = wow - 1;
    return (num ^ mask);
  }
};
