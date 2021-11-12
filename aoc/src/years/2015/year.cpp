#include "year.hpp"
#include "days.hpp"

namespace aoc::y2015 {
    // router
    const std::optional<Out> run(int day, const In &in) {
        switch (day) {
            case 1:
                return day01(in);
            default:
                return {};
        }
    }
}
