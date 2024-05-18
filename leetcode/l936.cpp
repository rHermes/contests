#include <algorithm>
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
  static std::vector<int> movesToStamp(const std::string& stamp, std::string& target)
  {
    const auto N = target.size();
    const auto SN = stamp.size();
    auto left = target.size();

    std::vector<int> out;

    while (left != 0) {
      const auto prePass = left;

      for (std::size_t i = 0; i < N - SN + 1; i++) {
        int removes = 0;
        bool matching = true;
        for (std::size_t j = 0; j < SN; j++) {
          if (target[i + j] != '?') {
            removes++;
            if (target[i + j] != stamp[j]) {
              matching = false;
              break;
            }
          }
        }

        if (!matching)
          continue;

        left -= removes;
        target.replace(i, SN, SN, '?');
        out.emplace_back(i);

        if (left == 0)
          break;
      }

      if (left == prePass)
        break;
    }

    if (left == 0) {
      std::ranges::reverse(out);
      return out;
    } else {

      return {};
    }
  }
};

int
main()
{
  return 0;
}
