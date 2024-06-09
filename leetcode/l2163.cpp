#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  [[gnu::pure]] static long long minimumDifference(const std::vector<int>& nums)
  {
    const int TN = nums.size();
    const int N = TN / 3;

    std::vector<long long> minReverse(N + 1, std::numeric_limits<long long>::max());

    std::vector<int> heap(nums.begin(), nums.begin() + N);
    std::ranges::make_heap(heap);

    long long fwdSum = 0;
    for (int i = 0; i < N; i++) {
      fwdSum += nums[i];
    }
    minReverse[0] = fwdSum;

    for (int i = 0; i < N; i++) {
      const auto x = nums[N + i];

      if (x < heap.front()) {
        fwdSum -= heap.front() - x;
        std::ranges::pop_heap(heap);
        heap.back() = x;
        std::ranges::push_heap(heap);
      }

      minReverse[i + 1] = fwdSum;
    }

    heap.assign(nums.begin() + 2 * N, nums.end());
    std::ranges::make_heap(heap, std::ranges::greater{});

    fwdSum = 0;
    for (int i = 2 * N; i < TN; i++) {
      fwdSum += nums[i];
    }

    long long ans = minReverse[N] - fwdSum;
    for (int i = N - 1; 0 <= i; i--) {
      const auto x = nums[N + i];

      if (heap.front() < x) {
        fwdSum += x - heap.front();
        std::ranges::pop_heap(heap, std::ranges::greater{});
        heap.back() = x;
        std::ranges::push_heap(heap, std::ranges::greater{});
      }

      ans = std::min(ans, minReverse[i] - fwdSum);
    }

    return ans;
  }
};
