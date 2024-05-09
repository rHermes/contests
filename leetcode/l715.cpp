#include <iostream>
#include <map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class RangeModule
{
  std::map<int, int> data;

public:
  void addRange(int left, int right)
  {
    if (data.empty()) {
      data.emplace(left, right);
      return;
    }

    auto beg = data.upper_bound(left);
    if (beg == data.begin()) {
      beg = data.emplace_hint(beg, left, right);
    } else {
      beg--;
      if (left <= beg->second) {
        beg->second = std::max(beg->second, right);
      } else {
        beg = data.emplace_hint(std::next(beg), left, right);
      }
    }

    // we now just have to check if we have merged something.
    // we to check if we hit the ones above.
    auto next = std::next(beg);
    while (next != data.end()) {
      if (next->first <= beg->second) {
        beg->second = std::max(beg->second, next->second);
        data.erase(next);
      } else {
        break;
      }

      next = std::next(beg);
    }
  }

  bool queryRange(int left, int right)
  {
    auto it = data.upper_bound(left);
    if (it == data.begin())
      return false;

    return right <= std::prev(it)->second;
  }

  void removeRange(int left, int right)
  {
    auto beg = data.lower_bound(left);
    if (beg != data.begin())
      beg--;

    while (beg != data.end()) {
      auto it = beg;
      beg++;

      if (right <= it->first) {
        break;
      }

      if (it->second <= left) {
        continue;
      }

      if (left <= it->first) {
        if (right < it->second) {
          data.emplace_hint(beg, right, it->second);
        }
        data.erase(it);
      } else {
        if (right < it->second) {
          data.emplace_hint(std::next(beg), right, it->second);
        }
        it->second = left;
      }
    }
  }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
int
main()
{
  return 0;
}
