#include <queue>
#include <set>
#include <tuple>

class Solution
{
public:
  int H(int pos, int speed, int target)
  {
    // we check how long it would take to get there.
    // we will stipulate that if we over shoot, we find the other way.

    if (pos == target)
      return 0;

    int answer = 0;

    if (pos < target) {
      if (speed < 0) {
        answer++;
        speed = 1;
      }

      while (pos < target) {
        answer++;
        pos += speed;
        speed *= 2;
      }
    } else {
      if (0 < speed) {
        answer++;
        speed = -1;
      }

      while (target < pos) {
        answer++;
        pos += speed;
        speed *= 2;
      }
    }
    return answer;
  }

  int racecar(int target)
  {
    // ok, so we will try to use A* for this.
    // we will use a simple huristic, to try to narrow down the
    // number of tests.

    // h(x), depth, pos, speed
    using T = std::tuple<int, int, int, int>;

    std::priority_queue<T, std::vector<T>, std::greater<T>> Q;
    Q.emplace(H(0, 1, target), 0, 0, 1);

    std::set<std::pair<int, int>> hey;
    while (!Q.empty()) {
      const auto [_, depth, pos, speed] = Q.top();
      Q.pop();

      if (auto it = hey.emplace(pos, speed); !it.second) {
        continue;
      }

      if (pos == target)
        return depth;

      Q.emplace(H(pos + speed, speed * 2, target) + depth + 1, depth + 1, pos + speed, speed * 2);

      // We only need to consider these changes if we are close to the point of impact.
      if ((0 < speed) && (target < (pos + speed)))
        Q.emplace(H(pos, -1, target) + depth + 1, depth + 1, pos, -1);
      else if ((speed < 0) && ((pos + speed) < target))
        Q.emplace(H(pos, 1, target) + depth + 1, depth + 1, pos, 1);
    }

    return -1;
  }
};
