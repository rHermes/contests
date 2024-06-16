#include <string>
class Solution
{
public:
  static std::string strWithout3a3b(int a, int b)
  {
    std::string out(a + b, ' ');
    int prevA = 0;
    int prevB = 0;
    int outIdx = 0;
    const int N = a + b;
    while (outIdx < N) {
      bool pickA = true;
      if (prevA == 2 || a < b)
        pickA = false;

      if (prevB == 2)
        pickA = true;

      if (pickA) {
        prevA += 1;
        prevB = 0;
        out[outIdx++] = 'a';
        a--;
      } else {
        prevB += 1;
        prevA = 0;
        out[outIdx++] = 'b';
        b--;
      }
    }

    return out;
  }
};
