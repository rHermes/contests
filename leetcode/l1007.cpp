#include <bitset>
#include <cstddef>
#include <vector>

class Solution
{
public:
  int minDominoRotations(std::vector<int>& tops, std::vector<int>& bottoms)
  {
    std::size_t N = tops.size();

    std::bitset<6> selector;
    selector.set();

    for (std::size_t i = 0; i < N; i++) {
      std::bitset<6> mask;
      mask.set(static_cast<std::size_t>(tops[i] - 1));
      mask.set(static_cast<std::size_t>(bottoms[i] - 1));

      selector &= mask;

      if (selector.count() == 0)
	return -1;
    }

    // std::cout << selector << std::endl;
    // We know there will be an answer here.
    std::size_t j = 0;
    for (; j < 6; j++) {
      if (selector[j]) {
	break;
      }
    }

    std::size_t topRow = 0;
    std::size_t common = 0;
    for (std::size_t i = 0; i < N; i++) {
      topRow += static_cast<std::size_t>(tops[i]) == (j + 1);
      common += tops[i] == bottoms[i];
    }
    return static_cast<int>(std::min(N - topRow, topRow - common));
  }
};

int
main()
{
  return 0;
}
