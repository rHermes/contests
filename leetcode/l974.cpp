#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
  static int subarraysDivByK(const std::vector<int> &nums, int k) {

    std::unordered_map<int, int> found{{0, 1}};

    int ans = 0;
    int accum = 0;
    for (const auto c : nums) {
      accum = (accum + (c % k) + k) % k;
      ans += found[accum]++;
    }

    return ans;
  }
};

static const auto __optimize__ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

int main() { return 0; }
