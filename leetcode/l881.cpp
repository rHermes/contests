#include <algorithm>
#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution {
public:
  static int numRescueBoats(std::vector<int> &people, int limit) {
    // The clue here is that we can always match up the heaviest
    // and lightests person.
    //
    // Why can we do this? We can do this, because if the heaviest member
    // can be combined with a person and not sink, then all other people
    // can be combined with that person and not sink.
    // This means that we are never excluding anyone from finding a partner
    // with a boat, by matching up the heaviest person. We could pick anyone
    // and it won't matter.
    std::sort(people.begin(), people.end());

    int lo = 0;
    int hi = people.size() - 1;

    int ans = 0;
    for (; lo <= hi; ans++) {
      if (people[lo] + people[hi--] <= limit)
        lo++;
    }

    return ans;
  }
};

int main() { return 0; }
