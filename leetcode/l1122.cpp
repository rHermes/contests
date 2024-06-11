#include <array>
#include <vector>
class Solution
{
public:
  static std::vector<int> relativeSortArray(std::vector<int> arr1, const std::vector<int>& arr2)
  {

    std::array<int, 1001> count{};
    for (const auto x : arr1)
      ++count[x];

    auto it = arr1.begin();
    for (auto x : arr2) {
      while (0 < count[x]--) {
        *(it++) = x;
      }
    }

    for (int i = 0; i < 1001; i++) {
      while (0 < count[i]--) {
        *(it++) = i;
      }
    }

    return arr1;
  }
};
