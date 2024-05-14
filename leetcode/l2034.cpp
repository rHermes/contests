#include <iostream>
#include <queue>
#include <unordered_map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

struct compare_max
{
  constexpr bool operator()(std::pair<int, int>& a, std::pair<int, int>& b) const { return a.second < b.second; }
};

struct compare_min
{
  constexpr bool operator()(std::pair<int, int>& a, std::pair<int, int>& b) const { return b.second < a.second; }
};

class StockPrice
{
  std::unordered_map<int, int> hist;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare_max> maxi;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare_min> mini;

  int lastTs{ -1 };
  int lastVal{ -1 };

public:
  void update(int timestamp, int price)
  {
    hist[timestamp] = price;

    if (lastTs <= timestamp) {
      lastVal = price;
      lastTs = timestamp;
    }

    maxi.emplace(timestamp, price);
    mini.emplace(timestamp, price);
  }

  int current() const { return lastVal; }

  int maximum()
  {
    auto mi = maxi.top();

    while (hist[mi.first] != mi.second) {
      maxi.pop();
      mi = maxi.top();
    }

    return mi.second;
  }

  int minimum()
  {
    auto mi = mini.top();

    while (hist[mi.first] != mi.second) {
      mini.pop();
      mi = mini.top();
    }

    return mi.second;
  }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */

int
main()
{
  return 0;
}
