#include "years/years.hpp"
#include "common/input.hpp"

#include <fmt/core.h>

int main() {
	for (int year = 2015; year <= 2025; year++) {
		for (int day = 1; day <= 25; day++) {
            auto input = aoc::get_input(year, day);
            if (!input) {
                continue;
            }
			aoc::In a(*input);
			if (auto out = aoc::run(year, day, a)) {
				printf("Y%04d D%02d: [%s] [%s]\n", year, day, out->part1.c_str(), out->part2.c_str());
			}
		}
	}
	return 0;
}
