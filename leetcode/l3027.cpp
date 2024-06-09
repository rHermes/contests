#include <algorithm>
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
  static int numberOfPairs(const std::vector<std::vector<int>>& givenPoints)
  {
    const int N = givenPoints.size();
    std::vector<std::pair<int, int>> points(N);
    for (int i = 0; i < N; i++) {
      points[i] = { givenPoints[i][0], -givenPoints[i][1] };
    }
    std::ranges::sort(points);

    int ans = 0;
    for (int i = 0; i < N; i++) {
      const auto& a = points[i];
      int limitY = std::numeric_limits<int>::max();
      for (int j = i + 1; j < N; j++) {
        const auto& b = points[j];
        if (b.second < a.second || limitY <= b.second)
          continue;

        limitY = b.second;
        ans++;
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
