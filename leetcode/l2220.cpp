#include <bit>

class Solution
{
public:
  static int minBitFlips(int start, int goal) { return std::popcount(static_cast<unsigned int>(start ^ goal)); }
};
