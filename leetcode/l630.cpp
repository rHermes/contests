#include <algorithm>
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
  static int scheduleCourse(std::vector<std::vector<int>>& courses)
  {
    std::ranges::sort(courses, [](const auto& a, const auto& b) {
      if (a[1] != b[1])
        return a[1] < b[1];
      return a[0] < b[0];
    });

    int cur = 0;
    std::priority_queue<int> Q;
    for (const auto& course : courses) {
      const auto lastDay = course[1];
      const auto dur = course[0];

      if ((cur + dur) <= lastDay) {
        Q.emplace(dur);
        cur += dur;
      } else if (!Q.empty() && dur < Q.top()) {
        cur -= (Q.top() - dur);
        Q.pop();
        Q.emplace(dur);
      }
    }

    return Q.size();
  }
};

int
main()
{
  return 0;
}
