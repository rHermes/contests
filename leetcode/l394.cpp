#include <charconv>
#include <iostream>
#include <string>
#include <string_view>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  // return how many characters we have consumed.
  static std::size_t decode(std::string& out, std::string_view left)
  {
    std::size_t consumed = 0;
    while (!left.empty()) {
      // first we are going to find if there are any numbers here.
      auto idx = left.find_first_of("123456789]");
      if (idx == left.npos) {
	out += left;
	consumed += left.size();
	break;
      }

      out += left.substr(0, idx);
      left.remove_prefix(idx);
      consumed += idx;

      if (left.front() == ']') {
	consumed++;
	break;
      }

      // We start on the first character.
      const auto bracketPos = left.find('[');
      int times             = 0;
      std::from_chars(left.data(), left.data() + bracketPos, times);
      consumed += bracketPos + 1;
      left.remove_prefix(bracketPos + 1);

      const auto currentSize = out.size();
      const auto subConsumed = decode(out, left);
      consumed += subConsumed;
      left.remove_prefix(subConsumed);

      const auto endSize = out.size();
      for (int i = 1; i < times; i++) {
	out.append(out.begin() + currentSize, out.begin() + endSize);
      }
    }

    return consumed;
  }

public:
  static std::string decodeString(const std::string& s)
  {
    std::string out;
    out.reserve(30);

    decode(out, s);

    return out;
  }
};

int
main()
{
  return 0;
}
