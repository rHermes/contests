#include <iostream>
#include <memory>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class CustomStack
{
  std::size_t m_cap;
  std::size_t m_tail{ 0 };
  std::unique_ptr<int[]> m_data{ std::make_unique_for_overwrite<int[]>(m_cap) };
  std::unique_ptr<int[]> m_inc{ std::make_unique<int[]>(m_cap) };

public:
  constexpr CustomStack(int maxSize) : m_cap(maxSize) {}

  constexpr void push(int x)
  {
    if (m_tail != m_cap) {
      m_data[m_tail++] = x;
    }
  }

  constexpr int pop()
  {
    if (m_tail == 0)
      return -1;

    m_tail--;

    const auto ret = m_data[m_tail] + m_inc[m_tail];
    if (m_tail != 0) {
      m_inc[m_tail - 1] += m_inc[m_tail];
    }

    m_inc[m_tail] = 0;

    return ret;
  }

  constexpr void increment(int k, int val)
  {
    auto level = std::min(static_cast<std::size_t>(k), m_tail);
    if (level != 0) {
      m_inc[level - 1] += val;
    }
  }
};
