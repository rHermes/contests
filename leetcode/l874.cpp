#include <complex>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

// credit: rhermes
struct MyHasher
{
  template<typename T, typename... Rest>
  void hash_combine(std::size_t& seed, const T& v, const Rest&... rest) const noexcept
  {
    seed ^= this->operator()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (hash_combine(seed, rest), ...);
  }

  template<typename T>
  constexpr std::size_t operator()(const T& s) const noexcept
  {
    return std::hash<T>{}(s);
  }

  template<typename A, typename B>
  constexpr std::size_t operator()(const std::pair<A, B>& pp) const noexcept
  {
    std::size_t seed = 0;
    hash_combine(seed, pp.first, pp.second);
    return seed;
  }

  template<typename... Ts>
  constexpr std::size_t operator()(const std::tuple<Ts...>& pp) const noexcept
  {
    std::size_t seed = 0;
    std::apply([&](const Ts&... args) { hash_combine(seed, args...); }, pp);
    return seed;
  }

  // Numeric values that we can pack into a single std::size_t
  template<std::integral S, std::integral T>
    requires((sizeof(T) + sizeof(S)) <= sizeof(std::size_t))
  constexpr std::size_t operator()(const std::pair<S, T>& p) const noexcept
  {
    return (static_cast<std::size_t>(p.first) << (8 * sizeof(T))) | static_cast<std::size_t>(p.second);
  }

  template<typename T>
  constexpr std::size_t operator()(const std::complex<T>& c) const noexcept
  {
    return this->operator()(std::make_pair(c.real(), c.imag()));
  }
};

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int robotSim(const std::vector<int>& commands, const std::vector<std::vector<int>>& obstacles)
  {
    using T = std::complex<int>;
    T position = { 0, 0 };
    T dir = { 0, 1 };

    std::unordered_set<T, MyHasher> seen;
    for (const auto& ob : obstacles) {
      seen.emplace(ob[0], ob[1]);
    }

    int ans = 0;
    for (auto x : commands) {
      if (0 <= x) {
        while (0 < x) {
          auto newS = position + dir;
          if (seen.count(newS))
            break;

          position = std::move(newS);
          x--;
        }
        ans = std::max(ans, std::norm(position));
      } else if (x == -2) {
        dir *= T{ 0, 1 };
      } else {
        dir *= T{ 0, -1 };
      }
    }

    return ans;
  }
};
