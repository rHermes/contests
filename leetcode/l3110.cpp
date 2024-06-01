#include <string>

class Solution
{
public:
  static int scoreOfString(const std::string& s)
  {
    int score = 0;
    for (std::size_t i = 0; i < s.size() - 1; i++)
      score += std::abs(s[i] - s[i + 1]);

    return score;
  }
};

int
main()
{
  return 0;
}
