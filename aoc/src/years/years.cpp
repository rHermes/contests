#include "years.hpp"
#include "2015/year.hpp"

const std::optional<aoc::Out> aoc::run(int year, int day, const aoc::In &in) {
  switch (year) {
  case 2015:
    return aoc::y2015::run(day, in);
  default:
    return {};
  }
}
