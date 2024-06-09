#include <iostream>
#include <vector>

static const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int subarraysDivByK(const std::vector<int>& nums, int k)
  {

    std::vector<int> found(k);
    found[0] = 1;

    int ans = 0;
    int accum = 0;
    for (const auto c : nums) {
      accum = (((accum + c) % k) + k) % k;
      ans += found[accum]++;
    }

    return ans;
  }
};

int
main()
{

  return 0;
}
