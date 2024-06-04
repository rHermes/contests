#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Bitset
{
  int m_N;
  std::string m_data;
  int m_count{ 0 };
  bool m_flipped{ false };

public:
  Bitset(int size) : m_N{ size }, m_data(size, '0') {}

  constexpr void fix(int idx)
  {
    if (m_flipped) {
      m_count -= m_data[idx] == '1';
      m_data[idx] = '0';
    } else {
      m_count += m_data[idx] != '1';
      m_data[idx] = '1';
    }
  }

  constexpr void unfix(int idx)
  {
    if (m_flipped) {
      m_count += m_data[idx] != '1';
      m_data[idx] = '1';
    } else {
      m_count -= m_data[idx] == '1';
      m_data[idx] = '0';
    }
  }

  constexpr void flip() { m_flipped = !m_flipped; }

  constexpr bool all()
  {
    if (m_flipped) {
      return m_count == 0;
    } else {
      return m_count == m_N;
    }
  }

  constexpr bool one()
  {
    if (m_flipped) {
      return m_count != m_N;
    } else {
      return m_count != 0;
    }
  }

  constexpr int count()
  {
    if (m_flipped) {
      return m_N - m_count;
    } else {
      return m_count;
    }
  }

  std::string toString()
  {
    if (m_flipped) {
      for (auto& c : m_data)
        c = (c == '1') ? '0' : '1';

      m_count = m_N - m_count;
      m_flipped = false;
    }
    return m_data;
  }
};

int
main()
{
  return 0;
}
