#include <iostream>
#include <unordered_map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class FrequencyTracker
{
  std::unordered_map<int, int> elems{};
  std::unordered_map<int, int> freqs{};

public:
  void add(int number)
  {
    auto [it, inserted] = elems.emplace(number, 1);
    if (!inserted) {
      freqs[it->second]--;
      it->second++;
    }
    freqs[it->second]++;
  }

  void deleteOne(int number)
  {
    auto it = elems.find(number);
    if (it == elems.end())
      return;

    if (it->second == 0)
      return;

    freqs[it->second]--;
    it->second--;
    if (it->second != 0) {
      freqs[it->second]++;
    }
  }

  bool hasFrequency(int frequency) const
  {
    auto it = freqs.find(frequency);
    return (it != freqs.end()) && (0 < it->second);
  }
};
