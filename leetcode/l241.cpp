#include <iostream>
#include <span>
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
  using CACHE = std::vector<std::vector<int>>;

  static const std::vector<int>& solve(CACHE& cache, const std::span<int>& exps, const int N, const int L, const int R)
  {
    const int key = L * N + R;
    if (!cache[key].empty()) {
      return cache[key];
    }

    if (R - L + 1 == 1) {
      cache[key] = { exps[L] };
      return cache[key];
    }

    for (int i = L + 1; i < R; i += 2) {
      const auto& leftParts = solve(cache, exps, N, L, i - 1);
      const auto& rightParts = solve(cache, exps, N, i + 1, R);

      for (const auto left : leftParts) {
        for (const auto right : rightParts) {
          if (exps[i] == -1) {
            cache[key].emplace_back(left - right);
          } else if (exps[i] == -2) {
            cache[key].emplace_back(left + right);
          } else {
            cache[key].emplace_back(left * right);
          }
        }
      }
    }

    return cache[key];
  }

public:
  static std::vector<int> diffWaysToCompute(const std::string& expression)
  {
    // -1 = -
    // -2 = +
    // -3 = *
    std::vector<int> numbers;

    int idx = 0;
    const int SN = expression.size();

    while (idx < SN) {
      int cur = 0;
      while (idx < SN && '0' <= expression[idx] && expression[idx] <= '9') {
        cur *= 10;
        cur += expression[idx++] - '0';
      }

      numbers.push_back(cur);

      if (idx == SN)
        break;

      switch (expression[idx++]) {
        case '*':
          numbers.push_back(-3);
          break;
        case '-':
          numbers.push_back(-1);
          break;
        case '+':
          numbers.push_back(-2);
          break;
      }
    }

    const int N = numbers.size();

    CACHE cache(N * N);
    return solve(cache, numbers, N, 0, N - 1);
  }
};
