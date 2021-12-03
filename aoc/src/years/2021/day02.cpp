#include "days.hpp"
#include <charconv>
#include <fmt/format.h>

using aoc::In;
using aoc::Out;

Out aoc::y2021::day02(const In &in) {
  std::string_view inp = in;

  int64_t a_x = 0;
  int64_t a_y = 0;
  int64_t b_y = 0;
  int64_t b_a = 0;

  while (!inp.empty()) {
    const auto k = inp.front();

    // We don't have to check anything but the first letter.
    if (k == 'f') {
      inp = inp.substr(8);
    } else if (k == 'd') {
      inp = inp.substr(5);
    } else {
      inp = inp.substr(3);
    }

    const auto snum = inp.substr(0, inp.find('\n'));
    inp = inp.substr(snum.length() + 1);

    int64_t num = 0;
    std::from_chars(snum.data(), snum.data() + snum.length(), num);

    if (k == 'f') {
      a_x += num;
      b_y += b_a * num;
    } else if (k == 'd') {
      a_y += num;
      b_a += num;
    } else {
      a_y -= num;
      b_a -= num;
    }
  }

  return {fmt::to_string(a_x * a_y), fmt::to_string(a_x * b_y)};
}
