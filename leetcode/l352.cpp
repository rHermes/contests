#include <cstdint>
#include <vector>

class SummaryRanges
{
  std::vector<std::pair<int, int>> ranges_;

  void merge()
  {
    if (ranges_.size() < 2)
      return;

    // ok, let's try to merge here.
    for (auto i = ranges_.size() - 1; 0 < i; i--) {
      auto ii = i - 1;

      auto& [al, ar] = ranges_[ii];
      auto& [bl, br] = ranges_[i];

      if (ar + 1 == bl) {
        ar = br;

        ranges_.erase(ranges_.begin() + static_cast<std::ptrdiff_t>(i));
      }
    }
  }

public:
  SummaryRanges() {}

  void addNum(int value)
  {
    // ok, let's search for this.
    if (ranges_.empty())
      ranges_.emplace_back(value, value);

    // we search
    std::size_t L = 0;
    std::size_t R = ranges_.size();

    while (L + 1 < R) {
      const auto C = (L + R) / 2;
      const auto& [l, r] = ranges_[C];

      if (value < l) {
        R = C;
      } else {
        L = C;
      }
    }

    // we now know where will insert the ranges.
    const auto& [l, r] = ranges_[L];
    // let's see if we are inside the data range.
    if (l <= value && value <= r) {
      return;
    }

    // ok, let's see where we should insert.
    if (value < l) {
      ranges_.insert(ranges_.begin() + static_cast<std::ptrdiff_t>(L), { value, value });
    } else {
      ranges_.insert(ranges_.begin() + static_cast<std::ptrdiff_t>(R), { value, value });
    }

    merge();
  }

  std::vector<std::vector<int>> getIntervals()
  {
    std::vector<std::vector<int>> ans;
    for (const auto& [l, r] : ranges_)
      ans.push_back({ l, r });

    return ans;
  }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
