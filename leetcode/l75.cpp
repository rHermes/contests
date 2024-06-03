#include <vector>
class Solution
{
public:
  static void sortColors(std::vector<int>& nums)
  {
    auto low = nums.begin();
    auto mid = low;
    auto high = nums.end() - 1;
    while (mid <= high) {
      if (*mid == 0) {
        std::swap(*low, *mid);
        low++;
        mid++;
      } else if (*mid == 2) {
        std::swap(*mid, *high);
        high--;
      } else {
        mid++;
      }
    }
  }
};

int
main()
{
  return 0;
}
