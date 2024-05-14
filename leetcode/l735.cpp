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
  static std::vector<int> asteroidCollision(const std::vector<int>& asteroids)
  {
    std::vector<int> out;

    for (auto a : asteroids) {
      if (0 < a) {
        out.emplace_back(a);
        continue;
      }

      while (!out.empty()) {
        const auto b = out.back();
        if (b < 0) {
          break;
        }

        if (b == -a) {
          out.pop_back();
          a = 0;
          break;
        }

        if (-a < b) {
          a = 0;
          break;
        } else {
          out.pop_back();
        }
      }

      // if we are empty or the last is negative.
      if (a != 0) {
        out.emplace_back(a);
        continue;
      }
    }

    return out;
  }
};

int main() { return 0; }
