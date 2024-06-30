#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MajorityChecker
{
  std::ranlux48 m_gen{ 0 };
  std::vector<int> m_arr;
  std::unordered_map<int, std::vector<int>> m_data;

  int countOccurances(int l, int r, int target)
  {
    const auto& kv = m_data[target];

    auto low = std::ranges::lower_bound(kv, l);
    auto hi = std::ranges::upper_bound(kv, r);

    return std::distance(low, hi);
  };

public:
  MajorityChecker(const std::vector<int>& arr) : m_arr{ arr }
  {
    for (std::size_t i = 0; i < m_arr.size(); i++) {
      m_data[m_arr[i]].push_back(i);
    }
  }

  int query(int left, int right, int threshold)
  {
    // ok, we are going to be sampling in that area now.
    std::uniform_int_distribution dist(left, right);

    for (int i = 0; i < 10; i++) {
      const auto elem = m_arr[dist(m_gen)];
      if (threshold <= countOccurances(left, right, elem))
        return elem;
    }

    return -1;
  }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
