#include "days.hpp"

#include <algorithm>
#include <charconv>
#include <string>
#include <tuple>

#include <fmt/format.h>

using aoc::In;
using aoc::Out;

static std::tuple<int, int, int> split_line(const std::string_view &line) {
  // TODO(rHermes): make this better, it's a mess right now
  auto l = line.substr(0, line.find("x"));
  auto w = line.substr(l.size() + 1, line.find("x", l.size() + 1) - (l.size() + 1));
  auto h = line.substr(l.size() + 1 + w.size() + 1);

  int li = 0;
  int wi = 0;
  int hi = 0;

  std::from_chars(l.data(), l.data() + l.size(), li);
  std::from_chars(w.data(), w.data() + w.size(), wi);
  std::from_chars(h.data(), h.data() + h.size(), hi);

  return std::make_tuple(li, wi, hi);
}

Out aoc::y2015::day02(const In &in) {
  uint64_t part1 = 0;
  uint64_t part2 = 0;

  In::size_type cur_pos = 0;
  auto linep = in.find("\n", cur_pos);
  while (linep != in.npos) {
    auto curline = in.substr(cur_pos, (linep - cur_pos));
    auto [l, w, h] = split_line(curline);

    part1 += 2 * (l * w + w * h + h * l) + std::min({l * w, w * h, h * l});
    part2 += l * w * h + 2 * std::min({l + w, w + h, h + l});

    cur_pos = linep + 1;
    linep = in.find("\n", cur_pos);
  }

  return Out{fmt::to_string(part1), fmt::to_string(part2)};
}
