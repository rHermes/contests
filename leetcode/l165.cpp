#include <string>

class Solution
{
public:
  [[gnu::hot, gnu::const]] static int compareVersion(const std::string& version1, const std::string& version2)
  {
    auto it1        = version1.cbegin();
    const auto end1 = version1.cend();

    auto it2        = version2.cbegin();
    const auto end2 = version2.cend();

    const auto parse = [](auto& it, const auto& end) {
      int num = 0;
      while (it != end) {
	const auto c = *(it++);
	if (c == '.') {
	  break;
	}
	num = num * 10 + (c - '0');
      }

      return num;
    };

    while (it1 != end1 || it2 != end2) {
      int num1 = parse(it1, end1);
      int num2 = parse(it2, end2);

      if (num1 < num2)
	return -1;

      if (num2 < num1)
	return 1;
    }

    return 0;
  }
};

int
main()
{
  return 0;
}
