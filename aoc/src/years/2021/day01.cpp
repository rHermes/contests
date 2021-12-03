#include "days.hpp"
#include <fmt/format.h>
#include <algorithm>
#include <charconv>

using aoc::In;
using aoc::Out;


// returns True if a < b
static constexpr bool comp(const std::string_view &a, const std::string_view &b) {
	if (a.length() != b.length()) {
		return a.length() < b.length();
	}
	return std::lexicographical_compare(a.cbegin(), a.cend(), b.cbegin(), b.cend());
}

Out aoc::y2021::day01(const In &in) {
	std::string_view inp = in;

	std::string_view a{"999999"}, b{"999999"}, c{"999999"};

	std::size_t part1 = 0;
	std::size_t part2 = 0;

	while (!inp.empty()) {
		const std::string_view d = inp.substr(0, inp.find(0xa));
		inp = inp.substr(d.size()+1);

		if (comp(c, d)) {
			part1++;
		}

		if (comp(a, d)) {
			part2++;
		}

		a = b;
		b = c;
		c = d;
	}


  return {fmt::to_string(part1), fmt::to_string(part2)};
}
