#include <iostream>
#include <string>
#include <string_view>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static std::string simplifyPath(const std::string& path)
  {
    using namespace std::string_view_literals;

    std::vector<std::string_view> dirs;
    std::size_t sz = 0;

    std::string_view view = path;

    while (!view.empty()) {
      const auto nextSlash = view.find('/', 1);
      auto comp = view.substr(0, nextSlash);
      if (nextSlash == view.npos)
        view = std::string_view();
      else
        view.remove_prefix(nextSlash);

      if (comp == "/"sv || comp == "/."sv) {
        continue;
      } else if (comp == "/.."sv) {
        if (!dirs.empty()) {
          sz -= dirs.back().size();
          dirs.pop_back();
        }
      } else {
        sz += comp.size();
        dirs.emplace_back(std::move(comp));
      }
    }

    if (dirs.empty())
      return "/";

    std::string answer;
    answer.reserve(sz);
    for (const auto& view : dirs) {
      answer += view;
    }

    return answer;
  }
};

int
main()
{
  return 0;
}
