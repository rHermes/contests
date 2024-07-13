#include <algorithm>
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
  struct Robot
  {
    int pos;
    int health;
    int idx;
  };

public:
  static std::vector<int> survivedRobotsHealths(const std::vector<int>& positions,
                                                const std::vector<int>& healths,
                                                const std::string& directions)
  {
    const int N = positions.size();

    std::vector<Robot> robots(N);
    for (int i = 0; i < N; i++) {
      robots[i] = { positions[i], healths[i], i };
    }

    std::ranges::sort(robots, [](const auto& a, const auto& b) { return a.pos < b.pos; });

    std::vector<Robot> out;
    std::vector<Robot> stack;
    for (auto& robot : robots) {
      if (directions[robot.idx] == 'R') {
        stack.emplace_back(robot);
        continue;
      }

      while (!stack.empty() && 0 < robot.health) {
        auto& top = stack.back();
        top.health--;
        robot.health--;
        if (top.health == robot.health) {
          robot.health = 0;
          stack.pop_back();
          break;
        } else if (top.health < robot.health) {
          stack.pop_back();
        } else {
          robot.health = 0;
          break;
        }
      }

      if (0 < robot.health) {
        out.push_back(robot);
      }
    }

    out.insert(out.end(), stack.begin(), stack.end());
    std::ranges::sort(out, [](const auto& a, const auto& b) { return a.idx < b.idx; });

    std::vector<int> ans(out.size());
    for (std::size_t i = 0; i < out.size(); i++) {
      ans[i] = out[i].health;
    }

    return ans;
  }
};
