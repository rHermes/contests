#pragma once
#include <complex>
#include <concepts>
#include <utility>

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
