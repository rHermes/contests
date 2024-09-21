#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static std::vector<int> lexicalOrder(const int N)
  {
    std::vector<int> out(N);

    int cur = 1;
    for (int idx = 0; idx < N; idx++) {
      out[idx] = cur;

      // if multiplying the current number by 10 is within the limit, we do so.
      if (cur * 10 <= N)
        cur *= 10;
      else {
        // We have to adjust the number up a digit instead.
        while (cur % 10 == 9 || N <= cur) {
          cur /= 10;
        }

        cur++;
      }
    }

    return out;
  }
};
