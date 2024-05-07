#include <cstdint>
#include <iostream>
#include <vector>

class CustomStack
{
  std::size_t cap_;
  std::vector<int> data_;

public:
  CustomStack(int maxSize) : cap_(static_cast<std::size_t>(maxSize)) { data_.reserve(cap_); }

  void push(int x)
  {
    if (data_.size() < cap_)
      data_.emplace_back(x);
  }

  int pop()
  {
    if (data_.empty())
      return -1;

    auto a = data_.back();
    data_.pop_back();
    return a;
  }

  void increment(int k, int val)
  {
    auto level = std::min(static_cast<std::size_t>(k), data_.size());
    for (std::size_t i = 0; i < level; i++)
      data_[i] += val;
  }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */

static const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

int
main()
{
  return 0;
}
