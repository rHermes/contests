#include <algorithm>
#include <vector>

class Solution
{
public:
  static std::vector<int> addNegabinary(std::vector<int>& arr1, std::vector<int>& arr2)
  {
    // The idea here is quite simple. Instead of a normal binary addition
    // with carry, the carry in negates any carry we have here.
    int carryIn = 0;
    // We want arr1 to be the one with the largest values.

    if (arr1.size() < arr2.size()) {
      using std::swap;
      swap(arr1, arr2);
    }

    std::vector<int> res;

    for (std::size_t i = 0; i < arr1.size(); i++) {
      int tot = arr1[arr1.size() - 1 - i] + carryIn;
      if (i < arr2.size())
        tot += arr2[arr2.size() - 1 - i];

      if (tot == 0) {
        res.emplace_back(0);
        carryIn = 0;
      } else if (tot == 1) {
        res.emplace_back(1);
        carryIn = 0;
      } else if (tot == 2) {
        res.emplace_back(0);
        carryIn = -1;
      } else if (tot == 3) {
        // So we need 3 of this one. this is the same as adding -1 of the next one and one of us
        res.emplace_back(1);
        carryIn = -1;
      } else if (tot == -1) {
        // We need the negative of this one. That means adding this
        // and one of the next ones.
        res.emplace_back(1);
        carryIn = 1;
      }
    }

    // now we have 2 options which requires further action.
    if (carryIn == 1) {
      res.emplace_back(1);
    } else if (carryIn == -1) {
      res.emplace_back(1);
      res.emplace_back(1);
    }

    // before we exit, we pop of any zeros.
    while (1 < res.size() && res.back() == 0) {
      res.pop_back();
    }

    std::reverse(res.begin(), res.end());

    return res;
  }
};

int
main()
{
  return 0;
}
