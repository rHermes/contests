#include <iostream>
#include <map>
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
  static int beautifulSubsets(std::vector<int>& nums, int k)
  {
    int totalCount = 1;
    std::unordered_map<int, std::map<int, int>> freqMap;
    for (const auto x : nums) {
      freqMap[x % k][x]++;
    }

    // we now just have to iterate through these.
    for (const auto& freq : freqMap) {
      int prevNum = -k;
      int prev2 = 0;
      int prev1 = 1;
      int curr = 0;

      for (const auto& [num, freq] : freq.second) {
        // We count the number of subsets skipping the current number.
        int skip = prev1;

        // we count subsets that include the current number
        int take;
        if (num - prevNum == k) {
          take = ((1 << freq) - 1) * prev2;
        } else {
          take = ((1 << freq) - 1) * prev1;
        }

        curr = skip + take;
        prev2 = prev1;
        prev1 = curr;
        prevNum = num;
      }

      totalCount *= curr;
    }

    return totalCount - 1;
  }
};
