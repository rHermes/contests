#include <iostream>
#include <stack>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution {
public:
  static bool isValid(const std::string &s) {
    std::stack<char> lol;

    for (const char c : s) {
      if (c == ')') {
        if (lol.empty() || lol.top() != '(')
          return false;
        lol.pop();
      } else if (c == '}') {
        if (lol.empty() || lol.top() != '{')
          return false;
        lol.pop();
      } else if (c == ']') {
        if (lol.empty() || lol.top() != '[')
          return false;
        lol.pop();
      } else {
        lol.push(c);
      }
    }

    return lol.empty();
  }
};

int main() { return 0; }
