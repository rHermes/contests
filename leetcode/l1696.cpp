#include <deque>
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
  static int maxResult(const std::vector<int>& nums, const int K)
  {
    const int N = nums.size();

    // we will keep a running trail of possibilities.
    std::deque<std::pair<int, int>> Q;

    Q.emplace_back(nums[0], 0);

    for (int i = 1; i < N; i++) {
      const int ourValue = Q.front().first + nums[i];

      while (!Q.empty() && Q.back().first <= ourValue) {
        Q.pop_back();
      }

      // We remove all who will go out of rotation next turn.
      while (!Q.empty() && Q.front().second <= (i - K)) {
        Q.pop_front();
      }

      Q.emplace_back(ourValue, i);
    }

    return Q.back().first;
  }
};
