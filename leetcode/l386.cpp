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
  static void fullRange(std::vector<int>& out, const int LIMIT, const int prefix)
  {
    for (int i = 0; i < 10; i++) {
      const int cur = prefix * 10 + i;
      if (LIMIT < cur)
        return;

      out.push_back(cur);
      fullRange(out, LIMIT, cur);
    }
  }

public:
  static std::vector<int> lexicalOrder(const int n)
  {
    std::vector<int> out;
    out.reserve(n);

    for (int i = 1; i <= 9; i++) {
      if (n < i)
        break;

      out.emplace_back(i);
      fullRange(out, n, i);
    }

    return out;
  }
};
