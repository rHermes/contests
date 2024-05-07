#include <cstdint>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

struct pcg32_random_r {
  std::uint64_t state;
  std::uint64_t inc;

  using result_type = std::uint32_t;

  constexpr static result_type min() { return 0; }
  constexpr static result_type max() { return std::numeric_limits<result_type>::max(); }

  result_type operator()() {
    std::uint64_t oldstate = state;
    // Advance internal state
    state = oldstate * 6364136223846793005ULL + (inc | 1);
    // Calculate output function (XSH RR), uses old state for max ILP
    std::uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    std::uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
  }
};

class RandomizedSet {
public:
  pcg32_random_r gen{123, 321};

  std::unordered_map<int, int> backwards;
  std::vector<int> forward;

  bool insert(int val) {
    auto [it, inserted] = backwards.emplace(val, forward.size());
    if (!inserted) {
      return false;
    }

    forward.emplace_back(val);
    return true;
  }

  bool remove(int val) {
    const auto it = backwards.find(val);
    if (it == backwards.end())
      return false;

    const int fwdKey = it->second;

    backwards[forward.back()] = fwdKey;
    forward[fwdKey] = forward.back();

    forward.pop_back();
    backwards.erase(it);
    return true;
  }

  int getRandom() { return forward[gen() % forward.size()]; }
};

int main() { return 0; }
