#include <iostream>
#include <string_view>
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
public:
  static std::vector<std::string> uncommonFromSentences(const std::string& s1, const std::string s2)
  {
    std::unordered_map<std::string_view, bool> seen;

    auto insertWord = [&seen](std::string_view word) {
      if (auto [it, inserted] = seen.emplace(std::move(word), true); !inserted) {
        it->second = false;
      }
    };

    auto insertSentence = [&](std::string_view line) {
      while (true) {
        auto nextPos = line.find(' ');
        if (nextPos == line.npos) {
          insertWord(line);
          break;
        }

        insertWord(line.substr(0, nextPos));
        line.remove_prefix(nextPos + 1);
      }
    };

    insertSentence(s1);
    insertSentence(s2);

    std::vector<std::string> out;
    out.reserve(seen.size());

    for (const auto& [word, unique] : seen) {
      if (unique) {
        out.emplace_back(word);
      }
    }

    return out;
  }
};
