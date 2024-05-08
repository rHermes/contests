#include <iostream>
#include <map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MyCalendar
{
public:
  std::map<int, int> periods;

  bool book(int start, int end)
  {
    auto it = periods.upper_bound(start);
    if (it != periods.begin()) {
      auto p = std::prev(it);
      if (start < p->second)
        return false;
    }

    if (it != periods.end() && it->first < end)
      return false;

    periods.emplace_hint(it, start, end);
    return true;
  }
};

int
main()
{
  return 0;
}
