#include <algorithm>
#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class KthLargest
{
  std::vector<int> m_data;

public:
  constexpr KthLargest(const int k, const std::vector<int>& nums) : m_data(k)
  {
    std::ranges::partial_sort_copy(nums, m_data, std::ranges::greater{});
    std::ranges::make_heap(m_data, std::ranges::greater{});
  }

  constexpr int add(int val)
  {
    if (m_data.front() < val) {
      std::ranges::pop_heap(m_data, std::ranges::greater{});
      m_data.back() = val;
      std::ranges::push_heap(m_data, std::ranges::greater{});
    }

    return m_data.front();
  }
};
