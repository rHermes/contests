#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

class Solution
{
public:
  std::string minWindow(std::string s, std::string t)
  {
    std::int64_t count = static_cast<std::int64_t>(t.size());
    std::vector<std::int32_t> needed('z' - 'A' + 1);

    for (const auto c : t)
      needed[static_cast<std::size_t>(c - 'A')]--;

    std::size_t l = 0;
    std::size_t r = 0;

    std::size_t minLen     = std::numeric_limits<std::size_t>::max();
    std::size_t startIndex = 0;

    while (r < s.size()) {
      auto found = needed[static_cast<std::size_t>(s[r] - 'A')]++;
      r++;
      if (found < 0)
	count--;

      while (count == 0) {
	auto found = needed[static_cast<std::size_t>(s[l] - 'A')]--;
	l++;
	if (found == 0) {
	  count++;

	  if ((r - l + 1) < minLen) {
	    startIndex = l - 1;
	    minLen     = r - l + 1;
	  }
	}
      }
    }

    if (minLen == std::numeric_limits<std::size_t>::max())
      return "";
    else
      return s.substr(startIndex, minLen);
  }
};

int
main()
{
  return 0;
}
