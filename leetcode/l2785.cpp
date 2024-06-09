#include <array>
#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  constexpr static int getIndex(const char c)
  {
    switch (c) {
      case 'A':
        return 0;
      case 'E':
        return 1;
      case 'I':
        return 2;
      case 'O':
        return 3;
      case 'U':
        return 4;
      case 'a':
        return 5;
      case 'e':
        return 6;
      case 'i':
        return 7;
      case 'o':
        return 8;
      case 'u':
        return 9;
      default:
        return -1;
    }
  }

public:
  static std::string sortVowels(std::string s)
  {
    std::array<int, 10> cnt{};
    constexpr std::array<char, 10> idx2chr{ 'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u' };

    for (char& c : s) {
      const auto idx = getIndex(c);
      if (idx != -1) {
        cnt[idx]++;
        c = '_';
      }
    }

    int pos = 0;
    for (char& c : s) {
      if (c != '_')
        continue;

      while (cnt[pos] == 0)
        pos++;
      --cnt[pos];

      c = idx2chr[pos];
    }

    return s;
  }
};
