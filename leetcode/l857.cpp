#include <algorithm>
#include <iostream>
#include <limits>
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
  static double mincostToHireWorkers(const std::vector<int>& quality, const std::vector<int>& wage, const int k)
  {
    const int N = quality.size();

    if (k == 1) {
      return *std::min_element(wage.begin(), wage.end());
    }

    std::vector<std::pair<double, int>> workers(N);
    for (int i = 0; i < N; i++) {
      workers[i] = { static_cast<double>(wage[i]) / quality[i], quality[i] };
    }

    std::sort(workers.begin(), workers.end());

    int sumQuality = 0;
    std::priority_queue<int> quals;

    int i = 0;
    for (; i < k - 1; i++) {
      sumQuality += workers[i].second;
      quals.push(workers[i].second);
    }

    double ans = std::numeric_limits<double>::max();
    for (; i < N; i++) {
      const auto [wagePerQ, qual] = workers[i];

      const auto myCost = wagePerQ * (qual + sumQuality);
      ans = std::min(ans, myCost);

      if (!quals.empty() && qual < quals.top()) {
        sumQuality -= quals.top() - qual;
        quals.pop();
        quals.push(qual);
      }
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
