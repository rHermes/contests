#include <algorithm>
#include <ranges>

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */
int
guess(int num);

class Solution
{
public:
  int guessNumber(int n)
  {
    auto it = std::views::iota(static_cast<unsigned int>(1), static_cast<unsigned int>(n) + 1);
    return *std::ranges::lower_bound(it, 0, [](const unsigned int cur, const unsigned int) {
      const int comp = guess(cur);
      return comp == 1;
    });
  }
};
