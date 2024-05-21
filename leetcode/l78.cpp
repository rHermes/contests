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
  static std::vector<std::vector<int>> subsets(const std::vector<int>& nums)
  {
    std::vector<std::vector<int>> out;

    // We just reserve the number we will need, to avoid some reallocations.
    out.reserve(1 << nums.size());

    // we insert the empty element. This is the base which we grow the
    // others on.
    out.emplace_back();

    for (std::size_t l = 0; l < nums.size(); l++) {

      // for each number, we are going to add them to the back of each
      // additional vector.
      const auto preSize = out.size();
      for (std::size_t j = 0; j < preSize; j++) {
        auto p = out[j];
        p.push_back(nums[l]);
        out.emplace_back(std::move(p));
      }
    }

    return out;
  }
};

int
main()
{
  return 0;
}
