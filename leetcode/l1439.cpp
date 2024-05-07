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
  static int kthSmallest(std::vector<std::vector<int>>& mat, int k)
  {
    const auto M = mat.size();
    const auto N = mat.front().size();

    if (M == 1) {
      return mat[0][k - 1];
    }

    std::vector<int> current;

    auto& reduced = mat[0];
    for (std::size_t row = 1; row < M; row++) {
      current.assign(k, std::numeric_limits<int>::max());

      // I am sure this could be done smartly, but let's just do it stupidly.
      for (std::size_t i = 0; i < reduced.size(); i++) {
	if (current[0] <= reduced[i])
	  continue;

	for (std::size_t j = 0; j < N; j++) {
	  const int sum = reduced[i] + mat[row][j];
	  if (current[0] <= sum)
	    break;

	  std::ranges::pop_heap(current);
	  current[k - 1] = sum;
	  std::ranges::push_heap(current);
	}
      }

      reduced = current;
    }

    std::ranges::sort_heap(current);
    return current[k - 1];
  }
};

int
main()
{
  return 0;
}
