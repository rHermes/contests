#include <stdexcept>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  std::vector<int> twoSum(std::vector<int>& nums, int target)
  {
    std::unordered_map<int, int> seen;
    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
      const auto n = nums[i];
      if (seen.count(target - n))
        return { i, seen[target - n] };

      seen.emplace(n, i);
    }

    throw std::runtime_error("this should not be reachable");
  }
};
