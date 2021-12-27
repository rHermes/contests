#include "year.hpp"
#include "days.hpp"

namespace aoc::y2021 {
// router
const std::optional<Out> run(int day, const In &in) {
  switch (day) {
  case 1:
    return day01(in);
  case 2:
    return day02(in);
  case 3:
    return day03(in);
  case 4:
    return day04(in);
  default:
    return {};
  }
}
} // namespace aoc::y2021
