#include <string>

class Solution
{
public:
  static std::string longestDiverseString(int a, int b, int c)
  {
    [[assume(0 <= a && 0 <= b && 0 <= c)]];
    [[assume(0 < a + b + c)]];
    std::string out;
    out.resize_and_overwrite(a + b + c, [ia = a, ib = b, ic = c](char* buf, std::size_t /* buf_size */) mutable {
      int taken = 0;

      int setA = 0;
      int setB = 0;
      int setC = 0;

      while (true) {
        const bool validA = setA != 2;
        const bool validB = setB != 2;
        const bool validC = setC != 2;

        [[assume(validA || (validB && validC))]];
        [[assume(validB || (validA && validC))]];
        [[assume(validC || (validA && validB))]];

        const bool cAB = !validB || (validA && (ib <= ia));
        const bool cAC = !validC || (validA && (ic <= ia));

        const bool cBC = !validC || (validB && (ic <= ib));
        const bool cBA = !validA || (validB && (ia <= ib));

        if (0 < ia && (cAB && cAC)) {
          buf[taken++] = 'a';
          ia--;
          setA++;
          setB = 0;
          setC = 0;
        } else if (0 < ib && (cBC && cBA)) {
          buf[taken++] = 'b';
          ib--;
          setB++;
          setA = 0;
          setC = 0;
        } else if (0 < ic && validC) {
          buf[taken++] = 'c';
          ic--;
          setC++;
          setA = 0;
          setB = 0;
        } else {
          break;
        }
      }

      return taken;
    });

    return out;
  }
};
