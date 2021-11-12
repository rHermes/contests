#pragma once

#include <optional>
#include <string>
#include <fstream>
#include <sstream>

#include <filesystem>
namespace fs = std::filesystem;

#include <fmt/core.h>

namespace aoc {

    // TODO(rHermes): Improve this system.
    std::optional<std::string> get_input(int year, int day) {
        std::string name = fmt::format("aoc/inputs/{:04d}-{:02d}.input", year, day);
        if (!fs::exists(name)) {
            return {};
        }

        std::ifstream t(name);
        std::stringstream buffer;
        buffer << t.rdbuf();

        return std::string(buffer.str());
    }
}
