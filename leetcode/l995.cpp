#include <iostream>
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
  using IT = std::conditional_t<std::same_as<T, bool>, char, T>;
  int m_n;
  std::vector<IT> m_data;

public:
  explicit BIT(int N) : m_n{ N + 1 }, m_data(m_n) {}

  constexpr void add(int r, T delta)
  {
    for (r++; r < m_n; r += r & -r) {
      if constexpr (std::same_as<T, bool>) {
        m_data[r] = (m_data[r] != delta);
      } else {
        m_data[r] += delta;
      }
    }
  }

  [[nodiscard]] constexpr T query(int r) const
  {
    T ret = 0;
    for (r++; 0 < r; r -= r & -r) {
      if constexpr (std::same_as<T, bool>) {
        ret = (m_data[r] != ret);
      } else {
        ret += m_data[r];
      }
    }
    return ret;
  }

  [[nodiscard]] constexpr T query(int l, int r) const
  {
    if (l == 0) {
      return query(r);
    } else {
      if constexpr (std::same_as<T, bool>) {
        return query(r) != query(l - 1);
      } else {
        return query(r) - query(l - 1);
      }
    }
  }
};

class Solution
{
public:
  static int minKBitFlips(const std::vector<int>& nums, int k)
  {
    const int N = nums.size();

    BIT<bool> tree(N + 1);

    int ans = 0;

    for (int i = 0; i < N - k + 1; i++) {
      if (nums[i] == 1) {
        tree.add(i, true);
        tree.add(i + 1, true);
      }

      if (!tree.query(i)) {
        ans++;
        tree.add(i, true);
        tree.add(i + k, true);
      }
    }

    for (int i = N - k + 1; i < N; i++) {
      if (nums[i] == 1) {
        tree.add(i, true);
        tree.add(i + 1, true);
      }

      if (!tree.query(i)) {
        return -1;
      }
    }

    return ans;
  }
};
