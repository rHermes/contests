#include <iostream>
#include <map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MyCalendarThree {
public:
  std::map<int, int> mp = {{-1, 0}, {1000000001, 0}};
  int maxans = 0;

  int book(int start, int end) {
    const auto [it_start, ins_start] = mp.emplace(start, 0);
    const auto [it_end, ins_end] = mp.emplace(end, 0);
    if (ins_start) {
      it_start->second = std::prev(it_start)->second;
    }

    if (ins_end) {
      it_end->second = std::prev(it_end)->second;
    }

    // we increase all keys between these two
    for (auto it = it_start; it != it_end; it++) {
      maxans = std::max(maxans, ++(it->second));
    }

    return maxans;
  }
};

int main() { return 0; }
