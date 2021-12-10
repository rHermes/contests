#include "days.hpp"
#include <fmt/format.h>

#include <array>
#include <iterator>

using aoc::In;
using aoc::Out;

Out aoc::y2021::day03(const In &in) {
  constexpr size_t N = 12;
  std::array<uint16_t, (1 << (N + 1)) - 1> tree;
  std::array<uint16_t, N> cum;

  for (auto at = in.begin(); at != in.end(); at++) {
    tree[0]++;

    size_t idx = 0;
    for (size_t i = 0; i < cum.size(); i++) {
      if (*at == '1') {
        cum[i]++;
        idx = idx * 2 + 2;
      } else {
        cum[i]--;
        idx = idx * 2 + 1;
      }

      tree[idx]++;
      at++;
    }
  }

  uint16_t gamma = 0;
  for (auto c : cum) {
    gamma <<= 1;
    if (2 * c > tree[0]) {
      gamma |= 1;
    }
  }

  // epsilon is simply the inverse of gamma.
  uint16_t epsilon = (~gamma) & ((1 << (N)) - 1);
  uint64_t part1 = gamma * epsilon;

  // We traverse the binary tree and pick the right paths for epsilon and gamma.
  gamma = 0;
  epsilon = 0;
  size_t g_idx = 0;
  size_t e_idx = 0;
  for (size_t i = 0; i < N; i++) {
    gamma <<= 1;
    epsilon <<= 1;

    g_idx = g_idx * 2 + 1;
    if (tree[g_idx] <= tree[g_idx + 1] || tree[g_idx] == 0) {
      g_idx++;
      gamma |= 1;
    }

    e_idx = e_idx * 2 + 1;
    if ((tree[e_idx + 1] < tree[e_idx] && tree[e_idx + 1] != 0) || tree[e_idx] == 0) {
      e_idx++;
      epsilon |= 1;
    }
  }

  return {std::to_string(part1), std::to_string(gamma * epsilon)};
}
