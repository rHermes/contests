#include <cstdint>
#include <iostream>
#include <vector>

using UT = std::uint64_t;
constexpr UT MODN = 1000000007;
constexpr int MAXN = 100000;

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class BIT
{
  int m_n;
  std::vector<int> m_data;

public:
  BIT(int n) : m_n{ n + 1 }, m_data(m_n, 0) {}

  constexpr void inc(int r)
  {
    for (r++; r < m_n; r += r & -r) {
      m_data[r] += 1;
    }
  }

  constexpr UT query(int r)
  {
    UT ret = 0;
    for (r++; 0 < r; r -= r & -r) {
      ret += m_data[r];
    }
    return ret;
  }

  constexpr UT query(int l, int r)
  {
    if (l == 0)
      return query(r);
    else {
      return (query(r) - query(l - 1)) % MODN;
    }
  }
};

class Solution
{

public:
  static int createSortedArray(std::vector<int>& instructions)
  {
    // one is the other. We can at each time always know.
    // This can be answered with a BIT actually
    BIT tree(MAXN + 1);

    int ans = 0;
    for (int i = 0; i < static_cast<int>(instructions.size()); i++) {
      const auto inst = instructions[i];
      ans += std::min(tree.query(inst - 1), i - tree.query(inst));
      ans %= MODN;

      tree.inc(inst);
    }
    return ans;
  }
};
