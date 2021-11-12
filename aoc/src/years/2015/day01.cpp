#include "days.hpp"
#include <string>

using aoc::Out;
using aoc::In;

Out aoc::y2015::day01(const In &in) {
	int floor = 0;
	int part2 = 0;
	int inst = 1;
	for (auto& c : in) {
		if (c == ')') {
			floor--;
		} else if (c == '(') {
			floor++;
		}

		if (floor == -1 && part2 == 0) {
			part2 = inst;
		}

		inst++;
	}

	return Out{std::to_string(floor), std::to_string(part2)};
}
