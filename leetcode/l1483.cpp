#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

// The depth of this tree will be very small, which is nice.
class TreeAncestor
{
  static constexpr int MAXK = 16;
  static constexpr int ROW = MAXK + 1;
  std::vector<int> m_jumps;

  constexpr auto getJump(int node, int level) const
  {
    if (node == -1)
      return -1;

    return m_jumps[node * ROW + level];
  }

public:
  TreeAncestor(int n, std::vector<int>& parent) : m_jumps(n * ROW)
  {

    for (int i = 0; i < n; i++) {
      m_jumps[i * ROW + 0] = parent[i];
    }

    for (int kth = 1; kth <= MAXK; kth++) {
      for (int i = 0; i < n; i++) {
        m_jumps[i * ROW + kth] = getJump(getJump(i, kth - 1), kth - 1);
      }
    }
  }

  constexpr int getKthAncestor(int node, const int k) const
  {
    auto cur = node;
    for (int kth = 0; kth <= MAXK; kth++) {
      if (k & (1 << kth)) {
        cur = getJump(cur, kth);
      }
    }
    return cur;
  }
};
