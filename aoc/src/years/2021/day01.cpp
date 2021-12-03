#include "days.hpp"
#include <charconv>
#include <fmt/format.h>
#include <limits>

using aoc::In;
using aoc::Out;

Out aoc::y2021::day01(const In &in) {
  std::string_view inp = in;

  uint64_t a = std::numeric_limits<uint64_t>::max();
  uint64_t b = a;
  uint64_t c = a;

  std::size_t part1 = 0;
  std::size_t part2 = 0;

  while (!inp.empty()) {
    const std::string_view line = inp.substr(0, inp.find('\n'));
    inp = inp.substr(line.size() + 1);

    uint64_t d = 0;
    std::from_chars(line.data(), line.data() + line.size(), d);

    if (c < d) {
      part1++;
    }

    if (a < d) {
      part2++;
    }

    a = b;
    b = c;
    c = d;
  }

  return {fmt::to_string(part1), fmt::to_string(part2)};
}
