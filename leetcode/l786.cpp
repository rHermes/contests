#include <iostream>
#include <numeric>
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
  static std::vector<int> kthSmallestPrimeFraction(const std::vector<int>& arr, const int k)
  {
    const int N = arr.size();

    double l = 0;
    double r = 1;

    while (l < r) {
      const auto mid = std::midpoint(l, r);
      int p = 0;
      int q = 1;
      int fractionsNotGreaterThanM = 0;

      // We will now find the amount of fractions that are greater than m.
      // we will update p and q to be the biggest fraction that is still
      // smaller than m. If the number of fractions which are larger than
      // M is k, then we know that we have our answer.

      // For each numerator, we are looking for the first j where arr[i] /
      // arr[j] < m
      for (int i = 0, j = 1; i < N; i++) {
        while (j < N && mid * arr[j] < arr[i])
          j++;

        if (j == N)
          break;

        fractionsNotGreaterThanM += N - j;

        // Check to see if we are
        if (p * arr[j] < arr[i] * q) {
          p = arr[i];
          q = arr[j];
        }
      }

      if (fractionsNotGreaterThanM == k) {
        return { p, q };
      } else if (fractionsNotGreaterThanM < k) {
        l = mid;
      } else {
        r = mid;
      }
    }
    throw std::runtime_error("Should not be reached");
  }
};
