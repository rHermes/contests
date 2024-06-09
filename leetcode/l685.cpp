#include <array>
#include <cstdint>
#include <vector>

class Solution
{
public:
  std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>>& edges)
  {
    // we can implement this with a dsu also. The main goal now, is that
    // all edges should be part of the same DSU.

    const auto N = edges.size();
    std::vector<std::uint16_t> rank(N, 1);
    std::vector<std::size_t> par(N, N);

    auto parent = [&par](std::size_t x) {
      auto root = x;
      while (par[root] != root)
        root = par[root];

      // ok, now we are in the top level node.
      // we iterate up again, to shorten it.
      while (x != root) {
        auto temp = x;
        x = par[x];
        par[temp] = root;
      }

      return x;
    };

    auto merge = [&rank, &par, &parent](std::size_t a, std::size_t b) {
      a = parent(a);
      b = parent(b);

      if (a == b)
        return false;

      if (rank[a] < rank[b]) {
        par[a] = b;
      } else {
        par[b] = a;
        if (rank[a] == rank[b])
          rank[a]++;
      }
      return true;
    };

    // we attempt to find two candidates for this.
    std::array<std::vector<int>, 2> candidates{};

    for (std::size_t i = 0; i < edges.size(); i++) {
      const auto src = static_cast<std::size_t>(edges[i][0] - 1);
      const auto dst = static_cast<std::size_t>(edges[i][1] - 1);

      // at this point, we are just investigating
      if (par[dst] == N) {
        par[dst] = src;
      } else {
        // ok we have a possible candidate here.
        candidates[0] = { static_cast<int>(par[dst] + 1), static_cast<int>(dst + 1) };
        candidates[1] = edges[i];
        // now we mark this edge, as it should not
        // be added.
        edges[i][1] = static_cast<int>(N + 1);
      }
    }

    // OK, now we reset the DSU, because we are going to be building it
    // again.
    for (std::size_t i = 0; i < N; i++)
      par[i] = i;

    // ok. Now we either have a duplicate pair, or we just construct the
    // graph until it's good.
    for (std::size_t i = 0; i < edges.size(); i++) {
      const auto src = static_cast<std::size_t>(edges[i][0] - 1);
      const auto dst = static_cast<std::size_t>(edges[i][1] - 1);

      if (dst == N)
        continue;

      if (!merge(src, dst)) {
        if (candidates[0].empty())
          return edges[i];
        else
          return candidates[0];
      }
    }

    // if we made it here, then skipping the second edge worked, so we
    // return it.
    return candidates[1];
  }
};
