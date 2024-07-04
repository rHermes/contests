#include <iostream>
#include <map>
#include <utility>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class SnapshotArray
{
  int m_gen{ 0 };
  std::map<std::pair<int, int>, int> m_data;

public:
  SnapshotArray(int) {}

  void set(int index, int val) { m_data[{ index, m_gen }] = val; }

  int snap() { return m_gen++; }

  int get(int index, int snap_id)
  {
    // we want to find the first one not less than the current one
    const auto key = std::make_pair(index, snap_id);
    auto it = m_data.upper_bound(key);
    if (it == m_data.begin())
      return 0;

    it = std::prev(it);
    const auto& [hIndex, hGen] = it->first;

    if (hIndex == index && hGen <= snap_id)
      return it->second;
    else
      return 0;
  }
};
