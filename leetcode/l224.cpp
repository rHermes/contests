#include <string>
#include <string_view>

class Solution
{
  static int eval(std::string_view& line)
  {
    int prev = 0;
    int cur = 0;
    char op = '+';

    const auto perf = [&] {
      if (op == '+') {
        prev += cur;
      } else {
        prev -= cur;
      }

      cur = 0;
    };

    while (!line.empty()) {
      const auto pp = line.find_first_not_of(' ');
      if (pp == line.npos) {
        line.remove_prefix(line.size());
        break;
      } else {
        line.remove_prefix(pp);
      }

      if (line[0] == '(') {
        line.remove_prefix(1);
        cur = eval(line);
      } else if (line[0] == ')') {
        line.remove_prefix(1);
        break;
      } else if (line[0] == '+') {
        perf();
        op = '+';
        line.remove_prefix(1);
      } else if (line[0] == '-') {
        perf();
        op = '-';
        line.remove_prefix(1);
      } else {
        // Now we just read until we don't have any more characters.
        int ans = 0;
        while (!line.empty() && '0' <= line[0] && line[0] <= '9') {
          ans *= 10;
          ans += line[0] - '0';
          line.remove_prefix(1);
        }
        cur = ans;
      }
    }

    perf();
    return prev;
  }

public:
  static int calculate(const std::string& s)
  {
    std::string_view view = s;
    return eval(view);
  }
};
