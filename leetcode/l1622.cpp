#include <cstdint>
#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Fancy
{
  using ST = std::int64_t;
  static constexpr ST MODN = 1000000007;
  std::vector<int> m_data;

  ST m_offset{ 0 };
  ST m_scale{ 1 };
  ST m_invScale{ 1 };

  static constexpr ST invMod(ST a)
  {
    if (a <= 1) {
      return a;
    } else {
      return MODN - (ST)(MODN / a) * invMod(MODN % a) % MODN;
    }
  }

  constexpr ST getInv()
  {
    if (m_invScale == -1)
      m_invScale = invMod(m_scale);

    return m_invScale;
  }

public:
  void append(int val)
  {
    val = (val - m_offset) % MODN;
    val = (val * getInv()) % MODN;
    val = (val + MODN) % MODN;
    m_data.push_back(val);
  }

  constexpr void addAll(int inc) { m_offset = (m_offset + inc) % MODN; }

  constexpr void multAll(int m)
  {
    m_offset = (m_offset * m) % MODN;
    m_scale = (m_scale * m) % MODN;
    m_invScale = -1;
  }

  constexpr int getIndex(int idx) const
  {
    if (static_cast<int>(m_data.size()) <= idx)
      return -1;

    ST ans = m_data[idx];

    ans = (ans * m_scale) % MODN;
    ans = (ans + m_offset) % MODN;

    return ans;
  }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
