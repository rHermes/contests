#include <algorithm>
#include <iostream>
#include <numeric>
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
  std::vector<int> m_sizes;

public:
  constexpr DSU(int n) : m_sz{ n }, m_parents(m_sz), m_sizes(m_sz, 1)
  {
    std::iota(m_parents.begin(), m_parents.end(), 0);
  }

  constexpr void clear()
  {
    std::iota(m_parents.begin(), m_parents.end(), 0);
    std::ranges::fill(m_sizes, 1);
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

    if (m_sizes[a] < m_sizes[b])
      std::swap(a, b);

    m_parents[b] = a;
    m_sizes[a] += m_sizes[b];
    return true;
  }

  [[nodiscard]] constexpr int group_size(int a) const { return m_sizes[parent(a)]; }
};

class Solution
{
  static constexpr bool connected(std::vector<std::vector<int>>& grid, const int ROWS, const int COLS, DSU& dsu)
  {
    int lastNode = 0;
    int seen = 0;

    dsu.clear();

    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (!grid[i][j])
          continue;

        lastNode = i * COLS + j;
        seen++;

        // ok, so we are just going to look down and right here.
        if (i < ROWS - 1 && grid[i + 1][j]) {
          dsu.merge(lastNode, lastNode + COLS);
        }

        if (j < COLS - 1 && grid[i][j + 1]) {
          dsu.merge(lastNode, lastNode + 1);
        }
      }
    }

    return (seen != 0) && (dsu.group_size(lastNode) == seen);
  }

public:
  static constexpr int minDays(std::vector<std::vector<int>>& grid)
  {
    // The answer is always going to be max 2, since there will always be
    // someone in the corner, or otherwise. This is interesting. It means
    // we really only need to iterate the rest of the graph.

    const int ROWS = grid.size();
    const int COLS = grid[0].size();

    DSU dsu(ROWS * COLS);

    if (!connected(grid, ROWS, COLS, dsu))
      return 0;

    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (!grid[i][j])
          continue;

        grid[i][j] = 0;
        bool con = connected(grid, ROWS, COLS, dsu);
        grid[i][j] = 1;
        if (!con) {
          return 1;
        }
      }
    }

    return 2;
  }
};
