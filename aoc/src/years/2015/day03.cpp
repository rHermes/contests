#include "days.hpp"

#include <algorithm>
#include <bitset>

#include <fmt/core.h>
#include <fmt/format.h>

using aoc::In;
using aoc::Out;

static size_t get_index(const size_t stride, const int x, const int y) { return y * stride + x; }

Out aoc::y2015::day03(const In &in) {
  // This makes an assumption about the input, but it's been safe for all inputs I've seen.
  const auto N = 200;
  const auto stride = 2 * N + 1;
  std::bitset<stride * stride> part1, part2;

  auto s1 = get_index(stride, N, N);
  auto s2 = s1;
  auto s3 = s1;

  part1[s1] = true;
  part2[s2] = true;

  bool sturn = true;
  for (auto c = in.begin(); c != std::prev(in.cend()); c++) {
    size_t offset = 0;
    switch (*c) {
    case '>':
      offset = 1;
      break;
    case '<':
      offset = -1;
      break;
    case '^':
      offset = -stride;
      break;
    case 'v':
      offset = stride;
      break;
    }

    s1 += offset;
    part1[s1] = true;

    if (sturn) {
      s2 += offset;
      part2[s2] = true;
    } else {
      s3 += offset;
      part2[s3] = true;
    }

    sturn = !sturn;
  }

  return Out{fmt::to_string(part1.count()), fmt::to_string(part2.count())};
}
