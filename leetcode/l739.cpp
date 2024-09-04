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
  static std::vector<int> dailyTemperatures(const std::vector<int>& temps)
  {
    const int N = temps.size();

    std::vector<int> out(N);
    out.back() = -1;

    for (int i = N - 2; 0 <= i; i--) {
      int j = i + 1;
      while (j != -1 && temps[j] <= temps[i]) {
        j = out[j];
      }
      out[i] = j;
    }

    for (int i = 0; i < N; i++) {
      if (out[i] == -1) {
        out[i] = 0;
      } else {
        out[i] = out[i] - i;
      }
    }

    return out;
  }
};
