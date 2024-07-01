#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();
class RangeFreqQuery
{
  std::unordered_map<int, std::vector<int>> m_data;

public:
  RangeFreqQuery(const std::vector<int>& arr)
  {
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
      m_data[arr[i]].push_back(i);
    }
  }

  int query(int left, int right, int value) const
  {
    auto it = m_data.find(value);
    if (it == m_data.end()) {
      return 0;
    }

    auto low = std::ranges::lower_bound(it->second, left);
    auto high = std::ranges::upper_bound(low, it->second.end(), right);
    return std::distance(low, high);
  }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
