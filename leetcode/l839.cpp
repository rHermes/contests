#include <iostream>
#include <numeric>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class DSU
{
  std::size_t m_size;
  mutable std::vector<int> m_parent;
  std::vector<int> m_sz;
  int m_groups{ static_cast<int>(m_size) };

public:
  DSU(std::size_t sz) : m_size{ sz }, m_parent(m_size), m_sz(m_size, 1)
  {
    std::iota(m_parent.begin(), m_parent.end(), 0);
  }

  [[nodiscard]] constexpr int parent(int a) const
  {
    auto root = a;
    while (root != m_parent[root])
      root = m_parent[root];

    while (a != root) {
      auto next = m_parent[a];
      m_parent[a] = root;
      a = next;
    }

    return root;
  }

  constexpr bool merge(int a, int b)
  {
    a = parent(a);
    b = parent(b);

    if (a == b)
      return false;

    m_groups--;

    if (m_sz[a] < m_sz[b]) {
      std::swap(a, b);
    }

    m_parent[b] = a;
    m_sz[a] += m_sz[b];
    return true;
  }

  [[nodiscard]] constexpr int groups() const { return m_groups; }
};

class Solution
{
public:
  static int numSimilarGroups(const std::vector<std::string>& strs)
  {
    const int N = strs.size();
    const int SN = strs.front().size();
    DSU dsu(N);

    for (int i = 0; i < N; i++) {
      const auto& a = strs[i];
      for (int j = 0; j < N; j++) {
        const auto& b = strs[j];

        if (dsu.parent(i) == dsu.parent(j))
          continue;

        int diff = 0;
        for (int k = 0; k < SN; k++) {
          if (a[k] != b[k]) {
            if (++diff == 3)
              break;
          }
        }

        if (diff <= 2)
          dsu.merge(i, j);
      }
    }

    return dsu.groups();
  }
};
