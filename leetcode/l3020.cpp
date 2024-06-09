#include <map>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  static int maximumLength(const std::vector<int>& nums)
  {
    std::map<long, long> ns;
    for (const auto n : nums)
      ns[n]++;

    std::unordered_map<int, int> dp;

    int ans = 1;
    for (const auto& [k, v] : ns) {
      if (k == 1) {
        ans = std::max(ans, static_cast<int>(v - (v % 2 == 0)));
        continue;
      }
      dp[k]++;
      ans = std::max(ans, 2 * dp[k] - 1);

      if (1 < v) {
        const int parent = k * k;
        auto it = ns.find(parent);
        if (it != ns.end()) {
          dp[parent] = dp[k];
        }
      }
    }

    // ok, we are going to be marking if they can be the
    return ans;
  }
};
