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
  static std::vector<int> twoSum(const std::vector<int>& numbers, int target)
  {
    int l = 0;
    int r = numbers.size() - 1;

    while (l != r) {
      const auto sum = numbers[l] + numbers[r];

      if (sum == target) {
        return { l + 1, r + 1 };
      } else if (sum < target) {
        l++;
      } else {
        r--;
      }
    }

    __builtin_unreachable();
  }
};

int
main()
{
  return 0;
}
