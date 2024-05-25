#include <bit>

class Solution
{
public:
  static int hammingWeight(int n) { return std::popcount(static_cast<unsigned int>(n)); }
};

int
main()
{
  return 0;
}
