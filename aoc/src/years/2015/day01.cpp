#include "days.hpp"
#include <fmt/format.h>

using aoc::In;
using aoc::Out;

Out aoc::y2015::day01(const In &in) {
  int floor = 0;
  int part2 = 0;
  int inst = 1;

  for (auto &c : in) {
    if (c == ')') {
      floor--;
      if (floor == -1 && part2 == 0) {
        part2 = inst;
      }
    } else if (c == '(') {
      floor++;
    }

    inst++;
  }

  return {fmt::to_string(floor), fmt::to_string(part2)};
}
