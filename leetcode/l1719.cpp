#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

template<typename T, std::size_t N>
class DSU
{
  mutable std::array<T, N> m_parent;
  std::array<T, N> m_size;

public:
  DSU()
  {
    std::iota(m_parent.begin(), m_parent.end(), 0);
    std::ranges::fill(m_size, 1);
  }

  [[nodiscard]] constexpr T parent(T id) const
  {
    auto root = id;
    while (root != m_parent[root]) {
      root = m_parent[root];
    }

    auto cur = id;
    while (m_parent[cur] != root) {
      auto next = m_parent[cur];
      m_parent[cur] = root;
      cur = next;
    }

    return root;
  }

  [[nodiscard]] constexpr T group_size(T id) const { return m_size[parent(id)]; }

  constexpr bool merge(T a, T b)
  {
    a = parent(a);
    b = parent(b);

    if (a == b) {
      return false;
    }

    if (m_size[a] < m_size[b]) {
      std::swap(a, b);
    }

    m_parent[b] = a;
    m_size[a] += m_size[b];

    return true;
  }
};

template<typename R, typename V>
concept RAR = std::ranges::random_access_range<R> && std::same_as<std::ranges::range_value_t<R>, V>;

class Solution
{
  static constexpr int MAXN = 500;
  using ST = std::int16_t;

  template<RAR<std::pair<int, int>> R>
  static int solve(R&& edges, R&& counts, const int numNodes, const int removed)
  {
    if (std::ranges::size(edges) == 0) {
      return 1;
    } else if (std::ranges::size(edges) == 1) {
      return 2;
    }

    DSU<ST, MAXN + 1> dsu;

    const int target = numNodes - 1 + removed;

    auto newCounts = std::ranges::partition(counts, [&](const auto& pp) { return target == pp.second; });

    for (auto it = counts.begin(); it != newCounts.begin(); it++) {
      dsu.merge(0, it->first);
    }

    const int numRoots = dsu.group_size(0) - 1;
    if (numRoots == 0) {
      return 0;
    }

    // Here is the exciting thing. We can just remove all the roots from the setup, as if we can do it with one, they
    // are exchangeable, as they have the exact same set of edges.

    const auto emptyGroup = dsu.parent(0);
    auto newEdges = std::ranges::partition(edges, [&](const auto& pp) {
      return (dsu.parent(pp.first) == emptyGroup) || (dsu.parent(pp.second) == emptyGroup);
    });

    for (const auto& [a, b] : newEdges) {
      dsu.merge(a, b);
    }

    auto localAns = std::clamp<int>(numRoots, 1, 2);
    while (!newEdges.empty()) {
      const auto groupParent = dsu.parent(newCounts.front().first);

      auto nextEdges =
        std::ranges::partition(newEdges, [&](const auto& pp) { return groupParent == dsu.parent(pp.first); });

      auto nextCounts =
        std::ranges::partition(newCounts, [&](const auto& pp) { return groupParent == dsu.parent(pp.first); });

      const auto innerAns = solve(std::ranges::subrange(newEdges.begin(), nextEdges.begin()),
                                  std::ranges::subrange(newCounts.begin(), nextCounts.begin()),
                                  dsu.group_size(groupParent),
                                  removed + numRoots);
      if (innerAns == 0) {
        return 0;
      }
      localAns = std::max(localAns, innerAns);

      newEdges = std::move(nextEdges);
      newCounts = std::move(nextCounts);
    }

    return localAns;
  }

public:
  static int checkWays(const std::vector<std::vector<int>>& PEARS)
  {
    std::unordered_map<int, int> count;

    std::vector<std::pair<int, int>> pairs;
    for (const auto& pair : PEARS) {
      pairs.emplace_back(pair[0], pair[1]);
      count[pair[0]]++;
      count[pair[1]]++;
    }

    int totalNodes = count.size();
    std::vector<std::pair<int, int>> counts;
    for (const auto& [id, cnt] : count) {
      counts.emplace_back(id, cnt);
    }

    return solve(pairs, counts, totalNodes, 0);
  }
};
