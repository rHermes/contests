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
  static std::vector<int> circularPermutation(int n, int start)
  {
    constexpr auto toGrey = [](int n) { return n ^ (n >> 1); };

    constexpr auto fromGrey = [](int g) {
      int n = 0;
      for (; g; g >>= 1)
        n ^= g;

      return n;
    };

    std::vector<int> out(1 << n);
    int startN = fromGrey(start);
    for (int i = 0; i < (1 << n); i++) {
      out[i] = toGrey(startN);
      startN = (startN + 1) % (1 << n);
    }

    return out;
  }
};
