#include <cmath>

class Solution
{
public:
  static int twoEggDrop(int n)
  {
    const double upper = std::sqrt(8.0 * n + 1) - 1;
    const double solution = std::ceil(upper / 2.0);
    return static_cast<int>(solution);
  }
};
