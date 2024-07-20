#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
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
  [[nodiscard]] constexpr int group_size(int a) const { return m_sz[parent(a)]; }
};

class Solution
{
public:
  static std::vector<int> groupStrings(const std::vector<std::string>& words)
  {
    using UT = std::uint32_t;
    const int N = words.size();
    DSU dsu(N);

    int largestGroup = 0;
    std::unordered_map<UT, int> bts2idx;
    for (int i = 0; i < N; i++) {
      UT bts = 0;
      for (const char c : words[i]) {
        bts |= 1 << (c - 'a');
      }

      // Now here is the secret sauce. If two strings can be transformed to the same string, via addition, then they
      // will work with the rules given. So it's enough to check for addition
      for (int idx = 0; idx < 26; idx++) {
        const auto newNum = bts | (1 << idx);
        if (newNum == bts)
          continue;

        if (auto it = bts2idx.find(newNum); it == bts2idx.end()) {
          bts2idx.emplace(newNum, i);
        } else {
          dsu.merge(i, it->second);
        }
      }

      if (auto it = bts2idx.find(bts); it == bts2idx.end()) {
        bts2idx.emplace(bts, i);
      } else {
        dsu.merge(i, it->second);
      }

      largestGroup = std::max(largestGroup, dsu.group_size(i));
    }
    return { dsu.groups(), largestGroup };
  }
};
