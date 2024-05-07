#include <bitset>

class Solution
{
public:
  int hammingDistance(int x, int y)
  {
    std::bitset<sizeof(int) * 8> xx(static_cast<unsigned long>(x));
    std::bitset<sizeof(int) * 8> yy(static_cast<unsigned long>(y));
    return static_cast<int>((xx ^ yy).count());
  }
};

int
main()
{
  return 0;
}
