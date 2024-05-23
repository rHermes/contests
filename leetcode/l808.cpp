#include <vector>

class Solution
{
public:
  constexpr static double soupServings(int n)
  {
    // This is the real trick. Since this converges on 1, we don't need to check
    // above this.
    if (4800 <= n) {
      return 1;
    }

    int servings = (n + 24) / 25;
    const int ROWS = servings + 1;

    std::vector<double> dp(ROWS * ROWS, 0.0);
    for (int i = 0; i < ROWS; i++) {
      dp[i] = 1;
      dp[i * ROWS] = 0;
    }
    dp[0 * ROWS + 0] = 0.5;

    for (int i = 1; i < ROWS; i++) {
      for (int j = 1; j < ROWS; j++) {

        const double a = dp[std::max(0, i - 4) * ROWS + j];
        const double b = dp[std::max(0, i - 3) * ROWS + std::max(0, j - 1)];
        const double c = dp[std::max(0, i - 2) * ROWS + std::max(0, j - 2)];
        const double d = dp[std::max(0, i - 1) * ROWS + std::max(0, j - 3)];

        dp[i * ROWS + j] = 0.25 * (a + b + c + d);
      }
    }

    return dp[servings * ROWS + servings];
  }
};

int
main()
{
  return 0;
}
