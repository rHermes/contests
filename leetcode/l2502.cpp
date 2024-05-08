#include <algorithm>
#include <unordered_map>
#include <vector>

class Allocator
{
  std::vector<std::pair<std::size_t, std::size_t>> freeBlocks_;
  std::unordered_map<int, std::vector<std::pair<std::size_t, std::size_t>>> takenBlocks_;

  void merge()
  {
    if (freeBlocks_.size() < 2)
      return;

    for (auto i = freeBlocks_.size() - 1; 0 < i; i--) {
      auto ii = i - 1;

      auto& [al, ar] = freeBlocks_[ii];
      auto& [bl, br] = freeBlocks_[i];
      if (ar == bl) {
        ar = br;

        freeBlocks_.erase(freeBlocks_.begin() + static_cast<std::ptrdiff_t>(i));
      }
    }
  }

public:
  Allocator(int n) { freeBlocks_.emplace_back(0, n); }

  int allocate(int size, int mID)
  {
    const auto sz = static_cast<std::size_t>(size);

    for (auto it = freeBlocks_.begin(); it != freeBlocks_.end(); it++) {
      auto& [l, r] = *it;

      if (sz <= (r - l)) {
        takenBlocks_[mID].emplace_back(l, l + sz);
        auto old = l;
        l += sz;

        return static_cast<int>(old);
      }
    }

    return -1;
  }

  int free(int mID)
  {
    auto it = takenBlocks_.find(mID);
    if (it == takenBlocks_.end())
      return 0;

    std::size_t ans = 0;
    for (const auto& p : it->second) {
      ans += p.second - p.first;
      const auto spot = std::upper_bound(freeBlocks_.begin(), freeBlocks_.end(), p);
      freeBlocks_.insert(spot, p);
    }

    takenBlocks_.erase(it);
    merge();
    return static_cast<int>(ans);
  }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->free(mID);
 */
int
main()
{
  return 0;
}
