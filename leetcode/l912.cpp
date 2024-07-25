
#include <iostream>
#include <ranges>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{

  template<std::ranges::random_access_range R>
  static constexpr void heapSort(R&& r)
  {

    constexpr auto iLeftChild = [](const int i) { return 2 * i + 1; };

    const int count = std::ranges::size(r);
    int start = count / 2;
    int end = count;

    while (1 < end) {
      if (0 < start) {
        start--;
      } else {
        end--;
        std::swap(r[0], r[end]);
      }

      int root = start;
      while (iLeftChild(root) < end) {
        int child = iLeftChild(root);
        if (child + 1 < end && r[child] < r[child + 1]) {
          child++;
        }

        if (r[root] < r[child]) {
          std::swap(r[root], r[child]);
          root = child;
        } else {
          break;
        }
      }
    }
  }

  template<std::ranges::random_access_range R>
  static constexpr auto getPivot(R&& r)
  {
    const auto ai = r.begin();
    const auto bi = r.begin() + (r.size() / 2);
    const auto ci = r.end() - 1;

    const auto a = *ai;
    const auto b = *bi;
    const auto c = *ci;

    if (a < b) {
      if (b < c) {
        return bi;
      } else if (c < a) {
        return ai;
      } else {
        return ci;
      }
    } else {
      if (c < b) {
        return bi;
      } else if (c < a) {
        return ai;
      } else {
        return ci;
      }
    }
  }

  template<std::ranges::random_access_range R>
  static constexpr void sortIt(R&& r, const int maxDepth)
  {
    // We need to
    const auto sz = std::ranges::size(r);
    if (sz <= 16) {
      for (int i = 1; i < static_cast<int>(sz); i++) {
        if (r[i - 1] <= r[i]) {
          continue;
        }
        const int val = r[i];

        int j = i - 1;
        while (0 < j && val < r[j - 1]) {
          // std::swap(r[j], r[j-1]);
          j--;
        }

        std::copy_backward(r.begin() + j, r.begin() + i, r.begin() + i + 1);
        r[j] = val;
      }
      return;
    } else if (maxDepth == 0) {
      // We have gotten a degen case of quicksort, so we abort this
      // attempt and instead switch over to heap sort.
      heapSort(r);
      return;
    }

    const auto beg = std::ranges::begin(r);
    const auto end = std::ranges::end(r);

    // pivot element is going to be the midway.
    const auto pivot = getPivot(r);
    const auto val = *pivot;

    // We swap the pivot to the front, to avoid non terminating searches.
    std::swap(*beg, *pivot);

    auto left = beg;
    auto right = end - 1;
    while (true) {
      while ((*left) < val) {
        left++;
      }

      while (val < (*right)) {
        right--;
      }

      if (right <= left)
        break;

      std::swap(*left, *right);
      left++;
      right--;
    }

    const auto pi = right + 1;
    const auto leftRange = std::ranges::subrange(beg, pi);
    const auto rightRange = std::ranges::subrange(pi, end);

    sortIt(leftRange, maxDepth - 1);
    sortIt(rightRange, maxDepth - 1);
  }

public:
  static constexpr std::vector<int> sortArray(std::vector<int>& nums)
  {
    const int maxDepth = (std::bit_width(nums.size()) - 1) * 2;
    sortIt(nums, maxDepth);
    return std::move(nums);
  }
};
