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
  int m_N;
  std::vector<T> m_data;

public:
  BIT(int N) : m_N{ N + 1 }, m_data(m_N, 0) {}

  void update(int idx, T delta)
  {
    for (++idx; idx < m_N; idx += idx & -idx) {
      m_data[idx] += delta;
    }
  }

  T sum(int idx)
  {
    T ret = 0;
    for (++idx; 0 < idx; idx -= idx & -idx) {
      ret += m_data[idx];
    }
    return ret;
  }

  T sum(int from, int to)
  {
    if (from == 0)
      return sum(to);

    return sum(to) - sum(from - 1);
  }

  void clear() { m_data.assign(m_N, 0); }
};

class Solution
{

public:
  static long long goodTriplets(const std::vector<int>& nums1, const std::vector<int>& nums2)
  {

    const int N = nums1.size();

    std::vector<int> n2idx(N);
    for (int i = 0; i < N; i++) {
      n2idx[nums1[i]] = i;
    }

    BIT<int> tree(N + 1);

    std::vector<int> smallerToRight(N);

    for (int i = N - 1; 0 <= i; i--) {
      // we are figuring out where we are in num21
      int index = n2idx[nums2[i]];

      smallerToRight[nums2[i]] = tree.sum(index + 1, N);

      tree.update(index + 1, 1);
    }

    long long ans = 0;

    tree.clear();

    for (int i = 0; i < N; i++) {
      int index = n2idx[nums2[i]];
      long long smallerElementsBefore = tree.sum(index);

      ans += smallerElementsBefore * smallerToRight[nums2[i]];

      tree.update(index + 1, 1);
    }

    return ans;
  }
};
