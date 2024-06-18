#include <vector>
class Solution
{
public:
  static constexpr bool checkPossibility(const std::vector<int>& nums)
  {
    // Let's think about this.
    const int N = nums.size();
    int i = 1;
    while (i < N) {
      if (nums[i - 1] <= nums[i]) {
        i++;
      } else {
        break;
      }
    }

    if (i == N)
      return true;

    if (i == 1) {
      i++;
    } else if (i == N - 1) {
      return true;
    } else {
      if (nums[i - 2] <= nums[i]) {
        i++;
      } else if (nums[i - 1] <= nums[i + 1]) {
        i++;
      } else {
        return false;
      }
    }

    while (i < N) {
      if (nums[i - 1] <= nums[i]) {
        i++;
      } else {
        break;
      }
    }

    return i == N;
  }
};
