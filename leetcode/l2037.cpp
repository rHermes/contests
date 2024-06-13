#include <algorithm>
#include <cmath>
#include <vector>

class Solution
{
public:
  int minMovesToSeat(std::vector<int>& seats, std::vector<int>& students)
  {
    // ok, so all these moves are sort of independent, which is a nice indicator.
    // They are not blocking each other.

    // let's start by sorting.
    std::ranges::sort(seats);
    std::ranges::sort(students);

    // ok, so we are going to be matching these up.
    int ans = 0;
    for (std::size_t i = 0; i < seats.size(); i++) {
      ans += std::abs(seats[i] - students[i]);
    }

    return ans;
  }
};
