#include <string>

class Solution
{
public:
  static constexpr int lengthOfLastWord(const std::string& s)
  {
    auto posLastChar = s.find_last_not_of(' ');
    if (posLastChar == s.npos)
      return 0;

    auto posLastSpace = s.find_last_of(' ', posLastChar);
    if (posLastSpace == s.npos) {
      return posLastChar + 1;
    }

    return posLastChar - posLastSpace;
  }
};
