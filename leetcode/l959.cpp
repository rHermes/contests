#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class DSU
{
  int m_sz;
  mutable std::vector<int> m_parents;
  std::vector<int> m_ranks;

public:
  constexpr DSU(int n) : m_sz{ n }, m_parents(m_sz), m_ranks(m_sz, 0)
  {
    std::iota(m_parents.begin(), m_parents.end(), 0);
  }

  [[nodiscard]] constexpr int parent(int n) const
  {
    int root = n;
    while (m_parents[root] != root)
      root = m_parents[root];

    int cur = n;
    while (m_parents[cur] != root) {
      cur = std::exchange(m_parents[cur], root);
    }

    return root;
  }

  constexpr bool merge(int a, int b)
  {
    a = parent(a);
    b = parent(b);

    if (a == b)
      return false;

    if (m_ranks[a] < m_ranks[b])
      std::swap(a, b);

    m_parents[b] = a;
    if (m_ranks[a] == m_ranks[b])
      m_ranks[a]++;

    return true;
  }
};

class Solution
{
public:
  static constexpr int regionsBySlashes(const std::vector<std::string>& grid)
  {
    // ok, more conservative. we put a marker half way on each gridline. This means
    // That we have alternating rows of N+1 and N
    const int N = grid.size();
    const int DOTS = N * (N + 1) + N * (N + 1);

    DSU dsu(DOTS);

    int ans = DOTS;
    for (int row = 0; row < N; row++) {
      for (int col = 0; col < N; col++) {
        const auto c = grid[row][col];

        // These are a bit hairy due to the alternating row lengths, But I think it works :)
        const int ABOVE = (row) * (N + 1) + (row)*N + col;
        const int BELOW = (row + 1) * (N + 1) + (row + 1) * N + col;

        const int LEFT = (row) * (N + 1) + (row + 1) * N + col;
        const int RIGHT = (row) * (N + 1) + (row + 1) * N + col + 1;

        if (c == '/') {
          ans -= dsu.merge(ABOVE, LEFT);
          ans -= dsu.merge(BELOW, RIGHT);
        } else if (c == '\\') {
          ans -= dsu.merge(ABOVE, RIGHT);
          ans -= dsu.merge(LEFT, BELOW);
        } else {
          ans -= dsu.merge(ABOVE, BELOW);
          ans -= dsu.merge(LEFT, RIGHT);
          ans -= dsu.merge(ABOVE, LEFT);
        }
      }
    }

    return ans;
  }
};
