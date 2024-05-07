#include <algorithm>
#include <string>

class Solution
{
public:
  std::string reversePrefix(std::string word, char ch)
  {
    const auto pos = word.find(ch);
    if (pos != word.npos) {
      reverse(word.begin(), word.begin() + pos + 1);
    }

    return word;
  }
};

int
main()
{
  return 0;
}
