#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

template<int N>
class FixedDSU
{
  // Sucks but we are just 0.6 bits to much to use a more compact type.
  std::array<std::int32_t, N> m_root{};
  std::array<std::int32_t, N> m_size{};

public:
  constexpr FixedDSU() { std::iota(m_root.begin(), m_root.end(), 0); }

  [[nodiscard]] constexpr int parent(int a)
  {
    if (m_root[a] != a) {
      m_root[a] = parent(m_root[a]);
    }

    return m_root[a];
  }

  [[nodiscard]] constexpr bool merge(int a, int b)
  {
    a = parent(a);
    b = parent(b);

    if (a == b) {
      return false;
    }

    if (m_size[a] < m_size[b])
      std::swap(a, b);

    m_root[b] = a;
    m_size[a] += m_size[b] + 1;
    return true;
  }

  [[nodiscard]] constexpr int size(int a)
  {
    a = parent(a);
    return m_size[a] + 1;
  }
};

class Solution
{
public:
  static constexpr int maxNumEdgesToRemove(int n, const std::vector<std::vector<int>>& edges)
  {
    constexpr int MAXN = 100000;
    int ans = 0;
    FixedDSU<MAXN> alice;
    FixedDSU<MAXN> bob;

    // We can avoid sorting the edges, by just looping twice.
    // The first time we are only looking for
    for (const auto& edge : edges) {
      if (edge[0] != 3)
        continue;

      const auto a = edge[1] - 1;
      const auto b = edge[2] - 1;

      auto builtAlice = alice.merge(a, b);
      auto builtBob = bob.merge(a, b);
      if (!builtAlice && !builtBob)
        ans++;
    }

    // Now we handle the normal edges
    for (const auto& edge : edges) {
      const auto a = edge[1] - 1;
      const auto b = edge[2] - 1;

      if (edge[0] == 1) {
        if (!alice.merge(a, b))
          ans++;
      } else if (edge[0] == 2) {
        if (!bob.merge(a, b))
          ans++;
      }
    }

    if (alice.size(0) != n || bob.size(0) != n)
      return -1;

    return ans;
  }
};
