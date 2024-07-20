#include <iostream>
#include <numeric>
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

  std::vector<int> m_val;

public:
  DSU(std::size_t sz) : m_size{ sz }, m_parent(m_size), m_sz(m_size, 1), m_val(m_size)
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
    m_val[a] += m_val[b];
    return true;
  }

  [[nodiscard]] constexpr int groups() const { return m_groups; }
  [[nodiscard]] constexpr int group_size(int a) const { return m_sz[parent(a)]; }

  [[nodiscard]] constexpr int get_value(int a) const { return m_val[parent(a)]; }

  constexpr void inc_value(int a) { m_val[parent(a)]++; }
};

class Solution
{
public:
  static int largestComponentSize(const std::vector<int>& nums)
  {
    constexpr int MAXV = 100000;
    std::vector<int> primes;
    std::vector<unsigned char> seen(MAXV + 1);
    const int SN = seen.size();
    for (int i = 0; i < SN; i += 2) {
      seen[i] = true;
    }
    primes.push_back(2);
    for (int i = 3; i < SN; i += 2) {
      if (seen[i])
        continue;

      primes.push_back(i);
      for (int j = i + i; j < SN; j += i) {
        seen[j] = true;
      }
    }

    const int N = nums.size();
    DSU dsu(primes.size());
    int largestGroup = 0;

    for (int i = 0; i < N; i++) {
      int tmp = nums[i];
      if (tmp == 1)
        continue;

      int prev = 0;

      while ((tmp % primes[prev]) != 0) {
        prev++;
      }

      while ((tmp % primes[prev]) == 0)
        tmp /= primes[prev];

      const int orig = prev;

      int next = prev + 1;
      while (1 < tmp) {
        while ((tmp % primes[next]) != 0)
          next++;

        while ((tmp % primes[next]) == 0)
          tmp /= primes[next];

        dsu.merge(prev, next);

        prev = next;
        next = prev + 1;
      }

      dsu.inc_value(orig);
      largestGroup = std::max(largestGroup, dsu.get_value(orig));
    }

    return largestGroup;
  }
};
