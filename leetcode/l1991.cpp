#include <numeric>
#include <vector>

class Solution
{
public:
  static int findMiddleIndex(const std::vector<int>& nums)
  {
    int totalSum = std::reduce(nums.begin(), nums.end(), 0);

    int curSum = 0;
    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
      if (curSum == totalSum - curSum - nums[i]) {
        return i;
      }

      curSum += nums[i];
    }

    return -1;
  }
};
