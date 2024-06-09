#include <iostream>
#include <vector>

class Solution
{
public:
  bool validPath(int n, std::vector<std::vector<int>>& edges, int source, int destination)
  {
    if (source == destination)
      return true;

    // we create a DSU to make this simpler.
    std::vector<int> parents(n + 1);
    for (std::size_t i = 0; i < parents.size(); i++) {
      parents[i] = i;
    }
    std::vector<int> ranks(n + 1, 1);

    const auto getParent = [&parents](int c) {
      auto root = c;
      while (parents[root] != root)
        root = parents[root];

      while (parents[c] != root) {
        auto par = parents[c];
        parents[c] = root;
        c = par;
      }

      return root;
    };

    const auto mergeSets = [&parents, &getParent, &ranks](int a, int b) {
      a = getParent(a);
      b = getParent(b);

      if (a == b)
        return false;

      if (ranks[a] < ranks[b]) {
        parents[a] = b;
      } else {
        if (ranks[a] == ranks[b])
          ranks[a]++;

        parents[b] = a;
      }
      return true;
    };

    for (const auto& pr : edges) {
      const auto aId = pr[0];
      const auto bId = pr[1];

      if (mergeSets(aId, bId)) {
        // This was a new connection, so we test.
        if (getParent(source) == getParent(destination))
          return true;
      }
    }

    return false;
  }
};

auto init = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 'c';
}();
