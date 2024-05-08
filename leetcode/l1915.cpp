#include <array>
#include <bitset>
#include <string>

class Solution
{

public:
  long long wonderfulSubstrings(std::string word)
  {

    long long ans = 0;
    std::array<int, 1024> cnt{};
    cnt[0] = 1;

    std::bitset<10> accum;
    for (std::size_t i = 0; i < word.size(); i++) {

      accum.flip(word[i] - 'a');

      // ok, now we have to check which prefixes we are just one away from.

      ans += cnt[accum.to_ulong()];

      for (std::size_t dig = 0; dig < 10; dig++) {
        accum.flip(dig);
        ans += cnt[accum.to_ulong()];
        accum.flip(dig);
      }

      cnt[accum.to_ulong()]++;
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
