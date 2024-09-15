#include <iostream>
#include <memory>
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
  static std::vector<int> xorQueries(const std::vector<int>& arr, const std::vector<std::vector<int>>& queries)
  {
    const int N = arr.size();
    auto psa = std::make_unique_for_overwrite<int[]>(N + 1);

    psa[0] = 0;
    for (int i = 0; i < N; i++) {
      psa[i + 1] = psa[i] ^ arr[i];
    }

    const int M = queries.size();
    std::vector<int> out(M);

    for (int i = 0; i < M; i++) {
      const auto& q = queries[i];
      out[i] = psa[q[1] + 1] ^ psa[q[0]];
    }

    return out;
  }
};
