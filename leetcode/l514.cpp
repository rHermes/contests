// Here is a godbolt with a lot more comparsions: https://godbolt.org/z/rWMf1aoq4
#include <array>
#include <limits>
#include <string>
#include <vector>

class Solution
{
public:
  int findRotateSteps(std::string ring, std::string key)
  {
    const int N = ring.size();

    const auto dist = [N](auto src, auto dst) {
      const auto diff = (src < dst) ? (dst - src) : (src - dst);
      return std::min(diff, N - diff);
    };

    std::array<std::vector<int>, 26> POS{};
    for (std::size_t i = 0; i < ring.size(); i++) {
      POS[ring[i] - 'a'].push_back(i);
    }

    std::array<int, 200> dp;
    int activeRow = 0;
    int otherRow  = 100;

    for (const auto idx : POS[key[0] - 'a']) {
      dp[activeRow + idx] = dist(0, idx);
    }

    for (std::size_t i = 1; i < key.size(); i++) {
      for (const auto target : POS[key[i] - 'a']) {
        int cost = std::numeric_limits<int>::max();
        for (const auto src : POS[key[i - 1] - 'a']) {
          cost = std::min(cost, dist(src, target) + dp[activeRow + src]);
        }

        dp[otherRow + target] = cost;
      }

      std::swap(activeRow, otherRow);
    }

    int ans = std::numeric_limits<int>::max();
    for (const auto idx : POS[key.back() - 'a']) {
      ans = std::min(ans, dp[activeRow + idx]);
    }

    return ans + key.size();
  }
};

int
main()
{
  return 0;
}
