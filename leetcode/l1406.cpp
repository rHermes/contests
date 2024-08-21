#include <iostream>
#include <string>
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
  static std::string stoneGameIII(const std::vector<int>& stoneValue)
  {
    const int N = stoneValue.size();

    std::vector<int> suffixSum(N + 1, 0);
    suffixSum[N - 1] = stoneValue[N - 1];
    for (int i = N - 2; 0 <= i; i--) {
      suffixSum[i] = stoneValue[i] + suffixSum[i + 1];
    }

    std::vector<int> dp(N + 1, 0);
    for (int i = N - 1; 0 <= i; i--) {
      int a = stoneValue[i] + (suffixSum[i + 1] - dp[i + 1]);
      if (i < N - 1) {
        a = std::max(a, stoneValue[i] + stoneValue[i + 1] + (suffixSum[i + 2] - dp[i + 2]));
      }

      if (i < N - 2) {
        a = std::max(a, stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2] + (suffixSum[i + 3] - dp[i + 3]));
      }

      dp[i] = a;
    }

    const int balance = 2 * dp[0] - suffixSum[0];
    if (balance == 0) {
      return "Tie";
    } else if (balance < 0) {
      return "Bob";
    } else {
      return "Alice";
    }
  }
};
