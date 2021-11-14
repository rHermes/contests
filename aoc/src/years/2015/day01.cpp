#include "days.hpp"
#include <fmt/format.h>

using aoc::In;
using aoc::Out;

Out aoc::y2015::day01(const In &in) {
  int part1 = 0;
  int part2 = -1;

  auto c = in.begin();
  auto end = std::prev(in.end());

  for (; c < end; c++) {
    if (*c == ')') {
      part1--;

      if (part1 == -1) {
        part2 = std::distance(in.begin(), c);
        c++;
        break;
      }
    } else {
      part1++;
    }
  }

  for (; c < end; c++) {
    if (*c == ')') {
      part1--;
    } else {
      part1++;
    }
  }

  return {fmt::to_string(part1), fmt::to_string(part2)};
}
