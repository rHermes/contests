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

template<typename R, typename V>
concept RAR = std::ranges::random_access_range<R> && std::same_as<std::ranges::range_value_t<R>, V>;

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

    if (m_size[b] < m_size[a]) {
      std::swap(a, b);
    }

    m_parent[a] = b;
    m_size[b] += m_size[a];

    return true;
  }
};

class Solution
{
  static constexpr int MAXN = 500;
  using ST = std::int16_t;

  using MEMARR = std::array<ST, MAXN + 1>;

  template<RAR<std::pair<int, int>> R>
  static int solve(R&& edges, R&& counts, const int numNodes, const int removed)
  {
    // ok, so we assume that all elements in this range is a single graph.
    // Then we just go through and we should keep track of an element.
    if (std::ranges::size(edges) == 0) {
      return 1;
    } else if (std::ranges::size(edges) == 1) {
      return 2;
    }

    DSU<ST, MAXN + 1> dsu;

    const int target = numNodes - 1 + removed;

    auto newCounts = std::ranges::partition(counts, [&](const auto& pp) { return target == pp.second; });

    auto potentialRoots = std::ranges::subrange(counts.begin(), newCounts.begin());
    if (potentialRoots.empty()) {
      return 0;
    }

    for (const auto& [k, v] : potentialRoots) {
      dsu.merge(0, k);
    }

    const auto emptyGroup = dsu.parent(0);
    // Here is the exciting thing. We can just remove all the roots from the
    // setup, as if we can do it with one, they are exchangeable, as they
    // have the exact same set of edges.
    auto newRange = std::ranges::partition(edges, [&](const auto& pp) {
      return (dsu.parent(pp.first) == emptyGroup) || (dsu.parent(pp.second) == emptyGroup);
    });

    // now comes the hard part. We must now parittion the remaining
    // elements into subgraphs.
    for (const auto& [a, b] : newRange) {
      dsu.merge(a, b);
    }

    // now we have our engines ready.
    auto localAns = 1;

    while (!newRange.empty()) {
      const auto groupParent = dsu.parent(newCounts.front().first);

      auto nextRange =
        std::ranges::partition(newRange, [&](const auto& pp) { return groupParent == dsu.parent(pp.first); });

      // We create our new nodes.
      auto nextCounts =
        std::ranges::partition(newCounts, [&](const auto& pp) { return groupParent == dsu.parent(pp.first); });

      auto innerAns = solve(std::ranges::subrange(newRange.begin(), nextRange.begin()),
                            std::ranges::subrange(newCounts.begin(), nextCounts.begin()),
                            dsu.group_size(groupParent),
                            removed + potentialRoots.size());
      if (innerAns == 0) {
        return 0;
      }
      localAns = std::max(localAns, innerAns);

      newRange = nextRange;
      newCounts = nextCounts;

      // add to 0, the seen set.
      dsu.merge(0, groupParent);
    }

    if (1 < potentialRoots.size()) {
      return 2;
    } else {
      return localAns;
    }
  }

public:
  static int checkWays(const std::vector<std::vector<int>>& PEARS)
  {
    // What if we only operate on the pairs themselves. We can always
    // partition it.
    // This can be precomputed if I wants

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
