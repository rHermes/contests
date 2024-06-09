#include <algorithm>
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
  static std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
  {
    const int N = nums.size();
    std::ranges::sort(nums);

    std::vector<std::vector<int>> out;

    for (int i = 0; i < N - 2; i++) {
      if (0 < nums[i])
        break;

      if (0 < i && nums[i - 1] == nums[i])
        continue;

      int k = N - 1;
      int j = i + 1;

      while (j < k) {
        const int sum = nums[i] + nums[j] + nums[k];

        if (sum < 0) {
          j++;
          while (j < k && nums[j - 1] == nums[j])
            j++;
        } else if (0 < sum) {
          k--;
          while (j < k && nums[k] == nums[k + 1])
            k--;
        } else {
          out.push_back({ nums[i], nums[j], nums[k] });

          j++;
          while (j < k && nums[j - 1] == nums[j])
            j++;

          k--;
          while (j < k && nums[k] == nums[k + 1])
            k--;
        }
      }
    }

    return out;
  }
};
