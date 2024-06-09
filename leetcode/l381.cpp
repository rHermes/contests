#include <cstdint>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

struct pcg32_random_r
{
  std::uint64_t state;
  std::uint64_t inc;

  using result_type = std::uint32_t;

  constexpr static result_type min() { return 0; }
  constexpr static result_type max() { return std::numeric_limits<result_type>::max(); }

  result_type operator()()
  {
    std::uint64_t oldstate = state;
    // Advance internal state
    state = oldstate * 6364136223846793005ULL + (inc | 1);
    // Calculate output function (XSH RR), uses old state for max ILP
    std::uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    std::uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
  }
};

class RandomizedCollection
{
public:
  pcg32_random_r gen{ 123, 321 };

  std::unordered_map<int, std::unordered_set<int>> val2idx;
  std::vector<int> idx2val;

  bool insert(int val)
  {
    auto& ids = val2idx[val];
    ids.emplace(idx2val.size());
    idx2val.push_back(val);

    return ids.size() < 2;
  }

  bool remove(int val)
  {
    const auto it = val2idx.find(val);
    if (it == val2idx.end())
      return false;

    auto& valFwds = it->second;

    // Figure out which index we are removing.
    const auto indexToRemapIt = valFwds.begin();
    const auto indexToRemap = *indexToRemapIt;
    valFwds.erase(indexToRemapIt);

    const int backIdx = idx2val.size() - 1;
    if (indexToRemap != backIdx) {
      const int otherVal = idx2val.back();
      const auto otherIt = val2idx.find(otherVal);

      otherIt->second.erase(backIdx);
      otherIt->second.insert(indexToRemap);

      idx2val[indexToRemap] = otherVal;
    }

    idx2val.pop_back();
    if (valFwds.empty())
      val2idx.erase(it);

    return true;
  }

  int getRandom() { return idx2val[gen() % idx2val.size()]; }
};
