#include <sstream>
#include <ranges>

struct MyFormat {
    template <typename T>
    static std::ostream& format(std::ostream& os, const T& obj) {
        os << obj;
        return os;
    }
};

template <>
std::ostream& MyFormat::format<std::pair<int,int>>(std::ostream& os, const std::pair<int,int>& obj) {
    os << "(" << obj.first << ", " << obj.second << ")";
    return os;
}



template <std::ranges::range R>
std::string printArray(R&& r) {
    using T = std::ranges::range_value_t<R>;

    std::ostringstream ss;
    auto it = std::ranges::begin(r);
    const auto end = std::ranges::end(r);

    ss << "[";

    bool first = true;
    while (it != end) {
        if (!first)
            ss << ", ";
        else
            first = false;
        
        MyFormat::format<T>(ss, *it);
        ++it;
    }
    ss << "]";
    return std::move(ss).str();
}
