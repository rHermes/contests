#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class TimeMap
{
public:
  std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> data;

  void set(const std::string& key, std::string value, int timestamp)
  {
    data[key].emplace_back(timestamp, std::move(value));
  }

  std::string get(const std::string& key, int timestamp) const
  {
    auto it = data.find(key);
    if (it == data.end()) {
      return "";
    }

    auto lel =
      std::ranges::upper_bound(it->second, timestamp, std::ranges::less{}, &std::pair<int, std::string>::first);
    if (lel == it->second.begin()) {
      return "";
    }

    return (--lel)->second;
  }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */

int
main()
{
  return 0;
}
