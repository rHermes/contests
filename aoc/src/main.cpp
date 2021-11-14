#include "common/input.hpp"
#include "years/years.hpp"

#include <chrono>
#include <ratio>

#include <fmt/chrono.h>
#include <fmt/core.h>

namespace chrono = std::chrono;
using namespace std::literals::chrono_literals;

int main() {
  auto dur = 0ns;
  for (int year = 2015; year <= 2025; year++) {
    for (int day = 1; day <= 25; day++) {

      auto input = aoc::get_input(year, day);
      if (!input) {
        continue;
      }
      aoc::In a(*input);

      auto start = chrono::steady_clock::now();
      auto out = aoc::run(year, day, a);
      auto end = chrono::steady_clock::now();
      auto diff = end - start;

      if (out) {
        dur += diff;
        auto print_diff = chrono::duration_cast<chrono::duration<double, std::micro>>(diff);
        fmt::print("{:04d}-{:02d}: {:>10s} | {:>10s} | {:>10.3}\n", year, day, out->part1,
                   out->part2, print_diff);
      }
    }
  }

  auto total_duration = chrono::duration_cast<chrono::duration<double, std::micro>>(dur);
  fmt::print("Total: {:.3}\n", total_duration);
  return 0;
}
