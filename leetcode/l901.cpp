#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class StockSpanner
{
  std::vector<std::pair<int, int>> m_data;

public:
  constexpr int next(int price)
  {
    int span = 1;
    while (!m_data.empty() && m_data.back().first <= price) {
      span += m_data.back().second;
      m_data.pop_back();
    }

    m_data.emplace_back(price, span);
    return span;
  }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
