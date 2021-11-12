#pragma once

#include "2015/year.hpp"


namespace aoc {
    const std::optional<Out> run(int year, int day, const In &in) {
		switch (year) {
			case 2015:
				return y2015::run(day, in);
			default:
				return {};
		}
	}
}
