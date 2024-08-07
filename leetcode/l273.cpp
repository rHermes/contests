#include <array>
#include <string>
#include <vector>

class Solution
{
  static constexpr std::array<std::string, 20> baseDigits{ {
    "Zero", "One",    "Two",    "Three",    "Four",     "Five",    "Six",     "Seven",     "Eight",    "Nine",
    "Ten",  "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen",
  } };

  static constexpr std::array<std::string, 8> prefixes{
    { "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" }
  };

  static constexpr std::array<std::string, 4> unitPlaces{ { "", " Thousand", " Million", " Billion" } };

  static constexpr void transWord(std::string& ans, const int num, const int step)
  {
    const int below = num % 100;
    const int hundred = num / 100;

    if (hundred != 0) {
      ans += baseDigits[hundred];
      ans += " Hundred";
    }

    if (below != 0) {
      if (hundred != 0) {
        ans.push_back(' ');
      }

      if (below < 20) {
        ans += baseDigits[below];
      } else {
        const int front = below / 10;
        const int back = below % 10;

        ans += prefixes[front - 2];
        if (back != 0) {
          ans.push_back(' ');
          ans += baseDigits[back];
        }
      }
    }

    ans += unitPlaces[step];
  }

public:
  static constexpr std::string numberToWords(int num)
  {
    if (num == 0) {
      return "Zero";
    }

    std::vector<int> parts;
    while (0 < num) {
      parts.push_back(num % 1000);
      num /= 1000;
    }

    std::string ans;
    int step = parts.size() - 1;
    for (auto it = parts.rbegin(); it != parts.rend(); it++) {
      if (*it != 0) {
        transWord(ans, *it, step);
        ans.push_back(' ');
      }
      step--;
    }
    ans.pop_back();

    return ans;
  }
};
