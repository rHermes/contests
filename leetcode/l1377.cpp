#include <iostream>
#include <vector>

class Solution
{
public:
  using graph_type = std::vector<std::vector<int>>;

  double frogPosition(int n, std::vector<std::vector<int>>& edges, int t, const int target)
  {
    // convert to a good graph
    graph_type G(n);

    // We assume here that the edges are only given once.
    for (const auto& pair : edges) {
      G[pair[0] - 1].push_back(pair[1] - 1);
      G[pair[1] - 1].push_back(pair[0] - 1);
    }

    // We do a BFS. in general we will hit our target this way, with a
    // higher base latency.
    std::vector<double> prob(n);
    prob[0] = 1.0;

    std::vector<bool> visited(n);
    visited[0] = true;

    // We are using two vectors here and swap between them, for each layer.
    // this makes it easier to process.
    std::vector<int> next;
    std::vector<int> current{ 0 };

    while (0 < t && !current.empty()) {
      // We process them 1 step at a time.
      for (const auto p : current) {
        // The root has no parents
        const auto posNext   = G[p].size() - (p != 0);
        const auto nextProbs = 1.0 / static_cast<double>(posNext) * prob[p];

        for (const auto child : G[p]) {
          if (visited[child])
            continue;

          visited[child] = true;
          prob[child]    = nextProbs;
          next.push_back(child);
        }

        // we have jumped past this.
        if (0 < posNext)
          prob[p] = 0;
      }

      // swap the current and the next
      using std::swap;
      swap(next, current);
      next.clear();

      // decrement the time after 1 jump.
      t--;
    }

    return prob[target - 1];
  }
};

int
main()
{
  return 0;
}
