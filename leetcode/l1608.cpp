#include <algorithm>
#include <numeric>
#include <vector>

class Solution
{
public:
  static int specialArray(std::vector<int>& nums)
  {
    const int N = nums.size();
    std::ranges::sort(nums);

    int beg = 0;
    int end = N;
    while (beg <= end) {
      const int mid = std::midpoint(beg, end);

      const int matching = std::distance(std::ranges::lower_bound(nums, mid), std::ranges::end(nums));

      if (matching < mid) {
        // Too few matching, we need to decrease
        end = mid - 1;
      } else if (mid < matching) {
        // To many matching, we need to increase
        beg = mid + 1;
      } else {
        // Since x is unique, this will be the solution
        return mid;
      }
    }

    return -1;
  }
};
