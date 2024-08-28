#include <iostream>
#include <memory>
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
  mutable std::unique_ptr<int[]> m_parents{ std::make_unique_for_overwrite<int[]>(m_sz) };
  std::unique_ptr<unsigned char[]> m_ranks{ std::make_unique_for_overwrite<unsigned char[]>(m_sz) };

public:
  DSU(int n) : m_sz{ n }
  {
    std::iota(m_parents.get(), m_parents.get() + m_sz, 0);
    std::fill_n(m_ranks.get(), m_sz, 0);
    // To nudge the water tile to be the desired merger.
    m_ranks[m_sz - 1] = 10;
  }

  [[nodiscard]] int parent(int n) const
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

  bool merge(int a, int b)
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
  static int countSubIslands(const std::vector<std::vector<int>>& grid1, const std::vector<std::vector<int>>& grid2)
  {
    const int ROWS = grid1.size();
    const int COLS = grid1[0].size();

    DSU dsu(ROWS * COLS + 1);

    // We use this to invalidate all groups who aren't sub groups
    const int failedNum = ROWS * COLS;

    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        const int key = i * COLS + j;

        if (!grid2[i][j]) {
          dsu.merge(failedNum, key);
          continue;
        }

        if (!grid1[i][j]) {
          dsu.merge(failedNum, key);
        }

        if (i < ROWS - 1 && grid2[i + 1][j]) {
          dsu.merge(key, key + COLS);
        }

        if (j < COLS - 1 && grid2[i][j + 1]) {
          dsu.merge(key, key + 1);
        }
      }
    }

    // Now we go through and find all who is not connected to the failed tile.
    int ans = 0;
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        ans += dsu.merge(failedNum, i * COLS + j);
      }
    }
    return ans;
  }
};
