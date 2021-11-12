#include "years/years.hpp"
#include "common/input.hpp"

#include <chrono>

#include <fmt/core.h>
#include <fmt/chrono.h>

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

            auto start = std::chrono::steady_clock::now();
            auto out = aoc::run(year, day, a);
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;

			if (out) {
                dur += diff;
                fmt::print("{:04d}-{:02d}: {:>10s} | {:>10s} | {:>10}\n", year, day, out->part1, out->part2, diff);
			}
		}
	}

    /* fmt::print("Total: {}\n", std::chrono::round<std::chrono::milliseconds>(dur)); */
    fmt::print("Total: {}\n", dur);
	return 0;
}
