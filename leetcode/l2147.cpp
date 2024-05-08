#include <cstdint>
#include <iostream>
#include <string>

class Solution
{
public:
  int numberOfWays(std::string corridor)
  {
    // ok, so we have a mission here.
    const auto N                = corridor.size();
    constexpr std::int64_t MODN = 1000000007;

    std::int64_t answer = 1;

    // we are just looking for runs of bushes.
    std::int8_t chairsSeen  = 0;
    std::int32_t plantsSeen = 0;
    for (std::size_t i = 0; i < N; i++) {
      if (corridor[i] == 'S') {
        chairsSeen++;

        if (chairsSeen == 3) {
          // ok, so we are going to put a divider one before this.
          answer = (answer * (plantsSeen + 1)) % MODN;

          chairsSeen = 1;
        } else if (chairsSeen == 2) {
          // ok, now we have seen two chairs. we reset the number of
          // plants seen.
          plantsSeen = 0;
        }
      } else {
        plantsSeen++;
      }
    }

    if (chairsSeen != 2)
      return 0;
    else
      return static_cast<int>(answer);
  }
};

const int init = []() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  return 0;
}();

int
main()
{
  return 0;
}
