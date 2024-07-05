#include <cstdint>
#include <iostream>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class BookMyShow
{
  using ST = std::int64_t;
  int m_rows;
  int m_seats;

  std::vector<ST> m_data;
  std::vector<ST> m_max;

  void build(int root, int targetL, int targetR)
  {
    if (targetL == targetR) {
      m_data[root] = m_seats;
    } else {
      const int targetM = std::midpoint(targetL, targetR);
      build(root * 2, targetL, targetM);
      build(root * 2 + 1, targetM + 1, targetR);
      m_data[root] = m_data[root * 2] + m_data[root * 2 + 1];
    }
  }

  ST sum(int root, int targetL, int targetR, int arrL, int arrR)
  {
    // We should figure out if it's at all possible.
    if (targetL == arrL && targetR == arrR) {
      return m_data[root];
    } else {
      const int targetM = std::midpoint(targetL, targetR);
      ST ans = 0;
      if (arrL <= targetM) {
        ans += sum(2 * root, targetL, targetM, arrL, std::min(arrR, targetM));
      }
      if (targetM < arrR) {
        ans += sum(2 * root + 1, targetM + 1, targetR, std::max(arrL, targetM + 1), arrR);
      }
      return ans;
    }
  }

  void removeScatter(int root, int targetL, int targetR, int arrL, int arrR, ST delta)
  {
    if (m_data[root] < delta) {
      throw std::runtime_error("Bad call to remove");
    }

    m_data[root] -= delta;

    // We stop once we reach a single.
    if (targetL == targetR) {
      m_max[root] -= delta;
      return;
    }

    const int targetM = std::midpoint(targetL, targetR);
    if (arrL <= targetM) {
      auto theyHave = m_data[2 * root];
      removeScatter(2 * root, targetL, targetM, arrL, std::min(arrR, targetM), std::min(theyHave, delta));

      delta -= std::min(theyHave, delta);
    }

    if (targetM < arrR) {
      removeScatter(2 * root + 1, targetM + 1, targetR, std::max(arrL, targetM + 1), arrR, delta);
    }

    m_max[root] = std::max(m_max[root * 2], m_max[2 * root + 1]);
  }

  std::optional<std::pair<int, int>> removeGather(int root,
                                                  int targetL,
                                                  int targetR,
                                                  int arrL,
                                                  int arrR,
                                                  const ST delta)
  {
    if (m_max[root] < delta) {
      return std::nullopt;
    }

    if (targetL == targetR) {
      const auto seat = m_seats - m_max[root];
      m_max[root] -= delta;
      m_data[root] -= delta;
      return std::make_pair(targetL, seat);
    }

    const int targetM = std::midpoint(targetL, targetR);
    if (arrL <= targetM) {

      auto res = removeGather(2 * root, targetL, targetM, arrL, std::min(arrR, targetM), delta);
      if (res) {
        m_data[root] -= delta;
        m_max[root] = std::max(m_max[root * 2], m_max[root * 2 + 1]);
        return res;
      }
    }

    if (targetM < arrR) {
      auto res = removeGather(2 * root + 1, targetM + 1, targetR, std::max(arrL, targetM + 1), arrR, delta);
      if (res) {
        m_data[root] -= delta;
        m_max[root] = std::max(m_max[root * 2], m_max[root * 2 + 1]);
        return res;
      }
    }

    return std::nullopt;
  }

public:
  BookMyShow(int n, int m) : m_rows{ n }, m_seats{ m }, m_data(4 * m_rows), m_max(4 * m_rows, m_seats)
  {
    build(1, 0, m_rows - 1);
  }

  std::vector<int> gather(int k, int maxRow)
  {
    auto res = removeGather(1, 0, m_rows - 1, 0, maxRow, k);
    if (!res) {
      return {};
    } else {
      return { res->first, res->second };
    }
  }

  bool scatter(int k, int maxRow)
  {
    if (sum(1, 0, m_rows - 1, 0, maxRow) < k)
      return false;

    removeScatter(1, 0, m_rows - 1, 0, maxRow, k);
    return true;
  }
};
