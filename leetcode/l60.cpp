#include <cstring>
#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static std::string getPermutation(const int n, int k)
  {
    std::string out(n, '1');
    for (int i = 2; i <= n; i++) {
      out[i - 1] = i + '0';
    }

    int factorial = 1;
    for (int i = 2; i < n; i++) {
      factorial *= i;
    }

    // We decrease it by one to make it work with modulus
    k--;
    for (int i = 0; i < n - 1; i++) {
      const auto firDig = k / factorial;

      if constexpr (true) {
        for (int j = i + firDig; i < j; j--) {
          std::swap(out[j - 1], out[j]);
        }
      } else {
        const char tmp = out[i + firDig];
        std::memmove(out.data() + i + 1, out.data() + i, firDig);
        out[i] = tmp;
      }

      k %= factorial;
      factorial /= (n - i - 1);
      if (k <= 0)
        break;
    }

    return out;
  }
};

int
main()
{
  return 0;
}
