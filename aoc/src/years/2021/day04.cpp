#include "days.hpp"

#include <algorithm>
#include <charconv>
#include <functional>
#include <limits>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

using aoc::In;
using aoc::Out;

static std::array<uint8_t, 25> parse_board(std::string_view &inp) {
  std::array<uint8_t, 25> out;
  std::size_t idx = 0;

  auto ptr = inp.data();
  auto end = inp.data() + inp.length();
  while (idx < out.max_size()) {
    while (*ptr == ' ') {
      ptr++;
    }

    uint8_t num = 0;
    auto [aptr, ec]{std::from_chars(ptr, end, num)};
    if (ec != std::errc()) {
      throw std::runtime_error("input format error");
    }
    ptr = aptr + 1;
    out[idx] = num;

    idx++;
  }

  inp = inp.substr(ptr - inp.data());

  return out;
}

// Returns round_finished and score
static std::pair<uint64_t, uint64_t> score_board(const std::unordered_map<uint8_t, uint8_t> &draws,
                                                 const std::array<uint8_t, 25> &board) {
  // We first transform the board into the index of the draws
  std::array<uint8_t, 25> iw;
  for (size_t i = 0; i < board.size(); i++) {
    iw[i] = draws.at(board[i]);
  }
  auto min_finish = std::numeric_limits<uint8_t>::max();

  // Rows
  for (size_t i = 0; i < 25; i += 5) {
    min_finish =
        std::min(min_finish, std::max({iw[i], iw[i + 1], iw[i + 2], iw[i + 3], iw[i + 4]}));
  }

  // Columns
  for (size_t i = 0; i < 5; i += 1) {
    min_finish =
        std::min(min_finish, std::max({iw[i], iw[i + 5], iw[i + 10], iw[i + 15], iw[i + 20]}));
  }

  // Score
  uint64_t ans = 0;
  uint8_t just_called = 0;
  for (size_t i = 0; i < board.size(); i++) {
    if (iw[i] > min_finish) {
      ans += board[i];
    }
    if (iw[i] == min_finish) {
      just_called = board[i];
    }
  }

  return {min_finish, ans * just_called};
}

Out aoc::y2021::day04(const In &in) {
  auto inp = in;

  std::unordered_map<uint8_t, uint8_t> draws;

  // Read in the draws.
  while (inp.front() != '\n') {
    const auto snum = inp.substr(0, inp.find_first_of(",\n"));
    inp = inp.substr(snum.length() + 1);

    uint8_t num = 0;
    auto [ptr, ec]{std::from_chars(snum.data(), snum.data() + snum.length(), num)};
    if (ec != std::errc()) {
      throw std::runtime_error("input format error");
    }

    draws.emplace(num, draws.size() + 1);
  }

  std::pair<uint64_t, uint64_t> p1{std::numeric_limits<uint64_t>::max(), 0}, p2{0, 0};

  while (inp.length() > 0) {
    // Skip new line
    inp = inp.substr(1);

    // This is to read in a board. It also modifies the "inp" to be at the next point
    auto board = parse_board(inp);
    auto res = score_board(draws, board);

    p1 = std::min(p1, res);
    p2 = std::max(p2, res);
  }

  return {fmt::to_string(p1.second), fmt::to_string(p2.second)};
}
