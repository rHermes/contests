// https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/
// https://codeforces.com/blog/entry/75627
//
#include <cinttypes>
#include <iostream>
#include <vector>

class Solution
{
public:
  int waysToBuildRooms(std::vector<int>& prevRoom)
  {
    using UT = std::uint64_t;
    const UT N = prevRoom.size();
    constexpr UT MODN = 1000000007;

    // we are going to be building a forward graph.
    std::vector<UT> facs(N);
    facs[0] = 1;
    for (UT i = 1; i < facs.size(); i++)
      facs[i] = (i * facs[i - 1]) % MODN;

    std::vector<std::vector<std::size_t>> G(N);
    for (UT i = 1; i < N; i++) {
      G[static_cast<std::size_t>(prevRoom[i])].push_back(i);
    }

    // We will also need an algorithm to calculate
    // inverses, since we are going to be divinding
    // in our
    // std::priority_queue<std::pair<int,std::
    return 0;
  }
};
