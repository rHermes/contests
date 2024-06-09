#include <bit>
#include <cstdint>
#include <string>

class Solution
{
public:
  static constexpr int longestPalindrome(const std::string& s)
  {
    // 57 is where it's at, but we are rounding up to 64
    std::uint64_t seen = 0;

    for (const auto c : s) {
      const unsigned int wb = c - 'A';
      seen ^= static_cast<std::uint64_t>(1) << wb;
    }

    const std::uint64_t left = std::popcount(seen);
    return s.size() - left + (left != 0);
  }
};
