#include <string>
#include <utility>
#include <map>
#include <cinttypes>
class UndergroundSystem {
public:
    std::map<int,std::pair<std::string,int>> inFlight;
    std::map<
    std::pair<std::string,std::string>,
    std::pair<std::uintmax_t,std::uintmax_t>
    > timings{};

    UndergroundSystem() {
    }
    
    void checkIn(int id, std::string stationName, int t) {
        inFlight.emplace(std::piecewise_construct,
        std::forward_as_tuple(id),
        std::forward_as_tuple(stationName, t)
        );
    }
    
    void checkOut(int id, std::string stationName, int t) {
        auto nh = inFlight.extract(id);
        const auto& [src, srcT] = nh.mapped();
        auto& lel = timings[{src, stationName}];
        lel.first += static_cast<std::uintmax_t>(t-srcT);
        lel.second += 1;
    }
    
    double getAverageTime(std::string startStation, std::string endStation) {
        const auto& [sum, num] = timings[{startStation, endStation}];
        return static_cast<double>(sum) / static_cast<double>(num);
    }
};

int main() {
}
