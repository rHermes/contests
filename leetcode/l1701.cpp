#include <cstdint>
#include <iostream>
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
  static constexpr double averageWaitingTime(const std::vector<std::vector<int>>& customers)
  {
    int chefTime = 0;
    std::int64_t totalWait = 0;
    for (const auto& customer : customers) {
      const auto arrived = customer[0];
      const auto spent = customer[1];

      chefTime = std::max(chefTime, arrived) + spent;
      totalWait += chefTime - arrived;
    }

    return static_cast<double>(totalWait) / customers.size();
  }
};
