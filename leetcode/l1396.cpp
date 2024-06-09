#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

template<typename T, typename... Rest>
void
hash_combine(std::size_t& seed, const T& v, const Rest&... rest)
{
  seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  (hash_combine(seed, rest), ...);
}

class UndergroundSystem
{
  using TimingsVal = std::pair<std::uintmax_t, std::uintmax_t>;

public:
  std::unordered_map<int, std::pair<std::string, int>> inFlight;
  std::unordered_map<std::size_t, TimingsVal> timings;

  void checkIn(int id, std::string stationName, int t)
  {
    inFlight.emplace(
      std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(std::move(stationName), t));
  }

  void checkOut(int id, const std::string& stationName, int t)
  {
    auto nh = inFlight.extract(id);
    const auto& [src, srcT] = nh.mapped();

    std::size_t seed = 0;
    hash_combine(seed, src, stationName);

    auto& lel = timings[seed];
    lel.first += (t - srcT);
    lel.second += 1;
  }

  double getAverageTime(const std::string& startStation, const std::string& endStation)
  {

    std::size_t seed = 0;
    hash_combine(seed, startStation, endStation);

    const auto& [sum, num] = timings[seed];
    return static_cast<double>(sum) / num;
  }
};
