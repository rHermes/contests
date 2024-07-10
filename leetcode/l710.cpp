#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  std::ranlux48 m_gen{ 0 };
  std::unordered_map<int, int> m_remap;
  std::uniform_int_distribution<int> m_dist;

public:
  Solution(int n, std::vector<int>& blacklist)
  {
    std::ranges::sort(blacklist);
    const int len = n - blacklist.size();

    auto bIt = blacklist.rbegin();
    auto good = n - 1;
    for (const auto x : blacklist) {
      if (len <= x)
        break;

      while (bIt != blacklist.rend() && *bIt == good) {
        bIt++;
        good--;
      }

      m_remap.emplace(x, good--);
    }
    m_dist = std::uniform_int_distribution<int>(0, len - 1);
  }

  int pick()
  {
    auto guess = m_dist(m_gen);
    if (auto it = m_remap.find(guess); it != m_remap.end()) {
      return it->second;
    } else {
      return guess;
    }
  }
};
