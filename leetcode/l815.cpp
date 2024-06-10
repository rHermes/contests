#include <iostream>
#include <limits>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int numBusesToDestination(const std::vector<std::vector<int>>& routes, const int source, const int target)
  {
    const int N = routes.size();

    if (source == target)
      return 0;

    int maxStop = 0;
    for (const auto& route : routes)
      for (const auto stop : route)
        maxStop = std::max(maxStop, stop);

    if (maxStop < target || maxStop < source)
      return -1;

    std::vector<int> dist(maxStop + 1, std::numeric_limits<int>::max());
    dist[source] = 0;

    bool changed = true;
    while (changed) {
      changed = false;

      for (const auto& route : routes) {

        int minToHere = N + 1;
        for (const auto stop : route)
          minToHere = std::min(minToHere, dist[stop]);

        ++minToHere;

        for (const auto stop : route) {
          if (minToHere < dist[stop]) {
            changed = true;
            dist[stop] = minToHere;
          }
        }
      }
    }

    if (dist[target] < N + 1) {
      return dist[target];
    } else {
      return -1;
    }
  }
};
