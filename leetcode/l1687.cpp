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
  static int boxDelivering(const std::vector<std::vector<int>>& boxes,
                           const int portsCount,
                           const int maxBoxes,
                           const int maxWeight)
  {
    std::ignore = portsCount;

    const int N = boxes.size();

    std::vector<int> dp(N + 1);

    int sum = 0;   // The current weight on the ship.
    int start = 0; // Load all boxes from start to r in one storage
    int diff = 0;  // different consecutive ports between start and r

    auto samePort = [&](const int idx) {
      if (idx == N - 1) {
        return false;
      } else {
        return boxes[idx][0] != boxes[idx + 1][0];
      }
    };

    const auto dropBox = [&] {
      sum -= boxes[start][1];
      diff -= samePort(start);
      start++;
    };

    const auto addBox = [&](const int idx) {
      if (idx != 0) {
        diff += samePort(idx - 1);
      }
      sum += boxes[idx][1];
    };

    for (int r = 0; r < N; r++) {
      // We drop 1 box because of the max boxes constraints.
      if (r - start == maxBoxes) {
        dropBox();
      }

      // We add the current box.
      addBox(r);

      // We keep dropping boxes, while we are overweight.
      while (maxWeight < sum) {
        dropBox();
      }

      // We are loading all packages in [start, r].
      // if dp[start] == dp[start+1], the first package can be included in the previous
      // shipment, without cost, and it makes no sense to include it in this one.
      while (start < r && dp[start] == dp[start + 1]) {
        dropBox();
      }

      dp[r + 1] = diff + 2 + dp[start];
    }

    return dp[N];
  }
};
