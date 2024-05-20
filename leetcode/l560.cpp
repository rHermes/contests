#include <iostream>
#include <unordered_map>
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
  static int subarraySum(const std::vector<int>& nums, int k)
  {
    // yeah, I got it. So we store the PSAs. Because what we are really
    // asking at this point is: Is there a psa[x] I can subtract from my
    // psa[y] that will be k.
    int ans = 0;
    int accum = 0;
    std::unordered_map<int, int> seen{ { 0, 1 } };

    for (const auto n : nums) {
      accum += n;

      // the reason we do it like this, is to avoid filling the map up
      // with useless values, that we haven't seen. In cases with a lot
      // of misses, this can save significant time.
      if (auto it = seen.find(accum - k); it != seen.end()) {
        ans += it->second;
      }

      seen[accum]++;
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
