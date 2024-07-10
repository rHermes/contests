#include <iostream>
#include <string>
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
  static constexpr int minOperations(const std::vector<std::string>& logs)
  {
    int depth = 0;

    for (const auto& op : logs) {
      if (op[0] != '.') {
        depth++;
      } else if (op[1] == '.') {
        depth = std::max(0, depth - 1);
      }
    }

    return depth;
  }
};
