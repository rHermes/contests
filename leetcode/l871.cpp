#include <cstdint>
#include <iostream>
#include <queue>
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
  static int minRefuelStops(int target, int startFuel, const std::vector<std::vector<int>>& stations)
  {
    using T = std::int32_t;

    std::priority_queue<T> fuels;
    T curPos = 0;
    T fuelLeft = startFuel;

    for (const auto& station : stations) {
      fuelLeft -= station[0] - curPos;
      curPos = station[0];

      while (fuelLeft < 0) {
        if (fuels.empty())
          return -1;

        fuelLeft += fuels.top();
        fuels.pop();
      }

      fuels.push(station[1]);
    }

    fuelLeft -= target - curPos;

    while (fuelLeft < 0) {
      if (fuels.empty())
        return -1;

      fuelLeft += fuels.top();
      fuels.pop();
    }

    return stations.size() - fuels.size();
  }
};

int
main()
{
  return 0;
}
