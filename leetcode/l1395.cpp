#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

template<typename T>
class BIT
{
  int m_N;
  std::vector<T> m_data;

public:
  constexpr BIT(int N) : m_N{ N + 1 }, m_data(m_N, 0) {}

  constexpr void update(int idx, T delta)
  {
    for (++idx; idx < m_N; idx += idx & -idx) {
      m_data[idx] += delta;
    }
  }

  constexpr T sum(int idx) const
  {
    T ret = 0;
    for (++idx; 0 < idx; idx -= idx & -idx) {
      ret += m_data[idx];
    }
    return ret;
  }
};

class Solution
{
public:
  static constexpr int numTeams(const std::vector<int>& rating)
  {
    // We solve this by first compressing the ratings into [0, N).
    // We then consider each soldier as the middle soldier in the solution.
    // We use a BIT to keep track off which values we have seen, and to be
    // able to quickly count how many soldiers are lower than this value.
    const int N = rating.size();

    std::vector<std::int16_t> idxs(N);
    std::iota(idxs.begin(), idxs.end(), 0);

    std::ranges::sort(idxs, [&](const auto i, const auto j) { return rating[i] < rating[j]; });

    std::vector<std::int16_t> compressed(N);
    for (int i = 0; i < N; i++) {
      compressed[idxs[i]] = i;
    }

    BIT<std::int16_t> left(N);

    int ans = 0;
    for (int i = 0; i < N; i++) {
      const auto x = compressed[i];

      const auto totalLower = x;
      const auto totalLarger = N - totalLower - 1;

      const auto leftLower = left.sum(x - 1);
      const auto leftLarger = i - leftLower;

      const auto rightLower = totalLower - leftLower;
      const auto rightLarger = totalLarger - leftLarger;

      ans += leftLower * rightLarger;
      ans += leftLarger * rightLower;

      left.update(x, 1);
    }

    return ans;
  }
};
