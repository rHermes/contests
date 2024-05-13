#include <algorithm>
#include <numeric>
#include <vector>

class Solution
{
public:
  static int candy(const std::vector<int>& ratings)
  {
    const int N = ratings.size();

    // We are going from the smallest to the
    std::vector<int> idx(N);
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), [&](const int i, const int j) { return ratings[i] < ratings[j]; });

    int ans = 0;
    std::vector<int> candies(N, 1);
    for (const auto i : idx) {
      if (0 < i) {
        if (ratings[i - 1] < ratings[i] && candies[i] <= candies[i - 1]) {
          candies[i] = candies[i - 1] + 1;
        }
      }

      if (i < N - 1) {
        if (ratings[i + 1] < ratings[i] && candies[i] <= candies[i + 1]) {
          candies[i] = candies[i + 1] + 1;
        }
      }

      ans += candies[i];
    }
    return ans;
  }
};

int
main()
{
  return 0;
}
