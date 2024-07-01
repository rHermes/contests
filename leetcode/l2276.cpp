#include <iostream>
#include <map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class CountIntervals
{
  std::map<int, int> m_data;
  int m_vals{ 0 };

public:
  void add(int left, int right)
  {
    // Increase the overla size.
    m_vals += right - left + 1;

    // Let's just make this easy.
    if (m_data.empty()) {
      m_data.emplace_hint(m_data.end(), left, right + 1);
      return;
    }

    // this is the first node that starts after us.
    const auto itStart = m_data.upper_bound(left);
    auto it = itStart;
    if (it == m_data.begin()) {
      // We are in the beginning, meaning that at least we will add
      // something.
      it = m_data.emplace_hint(it, left, right + 1);
    } else {
      // We now check if the one before us has a span into us
      auto itPrev = std::prev(it);
      if (left <= itPrev->second) {
        if (right < itPrev->second) {
          // we aren't adding anything
          m_vals -= right - left + 1;
          return;
        }

        m_vals -= itPrev->second - left;
        itPrev->second = right + 1;
        it = itPrev;
      } else {
        it = m_data.emplace_hint(it, left, right + 1);
      }
    }

    // Clean up now overlapped intervals
    for (auto next = std::next(it); next != m_data.end(); next = std::next(it)) {
      if (it->second < next->first)
        break;

      m_vals -= std::min(it->second, next->second) - next->first;
      it->second = std::max(it->second, next->second);

      m_data.erase(next);
    }
  }

  constexpr int count() const { return m_vals; }
};
