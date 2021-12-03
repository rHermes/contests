#include "years.hpp"
#include "2015/year.hpp"
#include "2021/year.hpp"

const std::optional<aoc::Out> aoc::run(int year, int day, const aoc::In &in) {
  switch (year) {
  case 2015:
    return aoc::y2015::run(day, in);
  case 2021:
	return aoc::y2021::run(day, in);
  default:
    return {};
  }
}
