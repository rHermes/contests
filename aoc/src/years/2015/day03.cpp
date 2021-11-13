#include "days.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <tuple>
#include <unordered_set>
#include <utility>

using aoc::In;
using aoc::Out;

template <class T> inline void hash_combine(std::size_t &seed, const T &v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
template <typename S, typename T> struct hash<pair<S, T>> {
  inline size_t operator()(const pair<S, T> &v) const {
    size_t seed = 0;
    ::hash_combine(seed, v.first);
    ::hash_combine(seed, v.second);
    return seed;
  }
};
} // namespace std

using Point = std::pair<int, int>;

static const Point perform_move(Point pos, char c) {
  const auto [x, y] = pos;
  switch (c) {
  case '>':
    return {x + 1, y};
  case '^':
    return {x, y + 1};
  case '<':
    return {x - 1, y};
  case 'v':
    return {x, y - 1};
  default:
    return {x, y};
  }
}

Out aoc::y2015::day03(const In &in) {
  std::unordered_set<Point> part1{std::make_pair(0, 0)};
  std::unordered_set<Point> part2{std::make_pair(0, 0)};

  Point s1{0, 0}, s2{0, 0}, s3{0, 0};

  bool sturn = true;
  for (auto &c : in) {
    s1 = perform_move(s1, c);
    part1.emplace(s1);

    if (sturn) {
      s2 = perform_move(s2, c);
      part2.emplace(s2);
    } else {
      s3 = perform_move(s3, c);
      part2.emplace(s3);
    }

    sturn = !sturn;
  }

  return Out{fmt::to_string(part1.size()), fmt::to_string(part2.size())};
}
