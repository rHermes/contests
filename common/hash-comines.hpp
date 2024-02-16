#pragma once
#include <functional>

// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
// More of what we need to do, in order to use something as a key.
// We need a comparitor and a hashing value.
// https://en.cppreference.com/w/cpp/language/default_comparisons
//
//


/* size_t hash_combine( size_t lhs, size_t rhs ) { */
/*   if constexpr (sizeof(size_t) >= 8) { */
/*     lhs ^= rhs + 0x517cc1b727220a95 + (lhs << 6) + (lhs >> 2); */
/*   } else { */
/*     lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2); */
/*   } */
/*   return lhs; */
/* } */



// Taken from https://stackoverflow.com/a/57595105
// More info on why?
// https://stackoverflow.com/a/27952689
template <typename T, typename... Rest>
void hash_combine(std::size_t& seed, const T& v, const Rest&... rest)
{
  if constexpr (sizeof(size_t) >= 8) {
    seed ^= std::hash<T>{}(v) + 0x517cc1b727220a95 + (seed << 6) + (seed >> 2);
  } else {
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	(hash_combine(seed, rest), ...);
}
