#include <algorithm>
#include <iostream>
#include <numeric>
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
  static constexpr int maxDistance(std::vector<int>& position, int m)
  {
    const int N = position.size();
    std::ranges::sort(position);

    auto isPossibleIteration = [&](const int dist) {
      int gotten = 1;
      int last = 0;
      for (int i = 1; i < N; i++) {
        if (dist <= (position[i] - position[last])) {
          gotten++;
          last = i;
          if (m <= gotten)
            break;
        }
      }

      return m <= gotten;
    };

    /*
auto isPossibleBinarySearch = [&](const int dist) {
int gotten = 1;
auto last = position.begin();
while (gotten < m) {
auto it = std::ranges::lower_bound(last + 1, position.end(), *last + dist);

if (it == position.end())
return false;

last = it;
gotten++;
}
return true;
};
    */

    int ans = 1;
    int lo = 0;
    int hi = position.back() - position.front() + 1;

    while (lo <= hi) {
      const int mid = std::midpoint(lo, hi);
      if (isPossibleIteration(mid)) {
        ans = mid;
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return ans;
  }
};
