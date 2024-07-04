#include <cstdint>
#include <list>
#include <vector>
class BookMyShow
{

  using ST = std::int64_t;
  ST m_rows;
  ST m_seats;
  ST m_left{ m_rows * m_seats };
  std::list<std::pair<ST, ST>> m_data;

public:
  BookMyShow(int n, int m) : m_rows{ n }, m_seats{ m }
  {
    for (int i = 0; i < m_rows; i++) {
      m_data.emplace_back(i * m_seats, (i + 1) * m_seats);
    }
  }

  // We are always eating from the front.
  // The front will almost always be the smallest?

  std::vector<int> gather(int k, int maxRow)
  {
    if (m_seats < k || m_left < k || m_data.empty())
      return {};

    for (auto it = m_data.begin(); it != m_data.end(); it++) {
      const auto start = it->first;
      const auto end = it->second;

      const auto curRow = start / m_seats;
      if (maxRow < curRow)
        return {};

      const auto sz = end - start;

      if (k <= sz) {
        const auto beg = start % m_seats;

        if (sz != k) {
          it->first = start + k;
        } else {
          m_data.erase(it);
        }

        m_left -= k;

        return { static_cast<int>(curRow), static_cast<int>(beg) };
      }
    }

    return {};
  }

  bool scatter(const int k, const int maxRow)
  {
    if (m_left < k || (maxRow + 1) < (k / m_seats)) {
      return false;
    }

    int curSeats = 0;
    for (auto it = m_data.begin(); it != m_data.end(); it++) {
      const auto start = it->first;
      const auto end = it->second;

      const auto curRow = start / m_seats;
      if (maxRow < curRow)
        break;

      const auto sz = end - start;
      curSeats += sz;

      if (curSeats < k) {
        continue;
      }

      const auto leftOver = curSeats - k;
      m_data.erase(m_data.begin(), it);

      if (leftOver != 0) {
        it->first = end - leftOver;
      } else {
        m_data.erase(it);
      }

      m_left -= k;
      return true;
    }
    return false;
  }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */
