#include <string>
#include <string_view>
class Solution
{
  static constexpr bool solve(std::string_view& exp)
  {
    const auto first = exp[0];
    exp.remove_prefix(1);

    if (first == 't') {
      return true;
    }

    if (first == 'f') {
      return false;
    }

    exp.remove_prefix(1);
    if (first == '!') {
      auto out = !solve(exp);
      exp.remove_prefix(1);
      return out;
    }

    bool out = first == '&';

    while (true) {
      bool thisOne = solve(exp);
      if (first == '&') {
        out &= thisOne;
      } else {
        out |= thisOne;
      }

      if (exp[0] == ')')
        break;
      else
        exp.remove_prefix(1);
    }
    exp.remove_prefix(1);

    return out;
  }

public:
  static constexpr bool parseBoolExpr(const std::string& expression)
  {
    std::string_view view = expression;
    return solve(view);
  }
};
