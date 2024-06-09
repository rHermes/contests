#include <vector>

class Solution
{
public:
  static int subsetXORSum(const std::vector<int>& nums)
  {
    unsigned int ans = 0;
    for (const auto n : nums)
      ans |= n;

    return ans << (nums.size() - 1);
  }
};
