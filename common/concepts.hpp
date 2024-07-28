#include <ranges>

template<typename R, typename V>
concept RAR = std::ranges::random_access_range<R> && std::same_as<std::ranges::range_value_t<R>, V>;

/* template<typename R, typename V> */
/* concept CRAR = RAR<R, V> && std::ranges::constant_range<R>; */
