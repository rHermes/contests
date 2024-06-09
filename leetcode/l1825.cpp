#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MKAverage
{
  bool ready_{ false };
  std::size_t cap_;
  std::size_t K_;
  std::size_t middleSize{ cap_ - 2 * K_ };
  std::size_t head_{ 0 };

  // We use a fixed vector, instead of a deque
  std::vector<int> data_;

  // We keep the vector around to minimize copying.
  std::multiset<int> right;
  std::multiset<int> middle;
  std::multiset<int> left;

  std::int64_t runningSum_{ 0 };

public:
  MKAverage(int m, int k) : cap_{ static_cast<std::size_t>(m) }, K_{ static_cast<std::size_t>(k) }, data_(cap_) {}

  void addElement(int num)
  {
    if (ready_) {
      const auto leavingElem = data_[head_];

      if (leavingElem <= *left.rbegin()) {
        left.erase(left.find(leavingElem));
      } else if (*right.begin() <= leavingElem) {
        right.erase(right.find(leavingElem));
      } else {
        middle.erase(middle.find(leavingElem));
        runningSum_ -= leavingElem;
      }
    }
    data_[head_] = num;
    head_ = (head_ + 1) % cap_;

    if (!ready_ && head_ == 0) {
      ready_ = true;

      auto vec = data_;
      std::sort(vec.begin(), vec.end());

      auto kMiddleStart = vec.begin() + K_;
      auto kMiddleEnd = vec.begin() + (cap_ - K_);

      left.insert(vec.begin(), kMiddleStart);
      middle.insert(kMiddleStart, kMiddleEnd);
      right.insert(kMiddleEnd, vec.end());

      runningSum_ = 0;
      for (auto it = kMiddleStart; it != kMiddleEnd; it++) {
        runningSum_ += *it;
      }
      return;
    }

    if (!ready_)
      return;

    runningSum_ += num;
    middle.emplace(num);

    if (left.size() != K_) {
      auto nh = middle.extract(middle.begin());
      runningSum_ -= nh.value();
      left.insert(left.end(), std::move(nh));
    } else if (right.size() != K_) {
      auto nh = middle.extract(std::prev(middle.end()));
      runningSum_ -= nh.value();
      right.insert(right.begin(), std::move(nh));
    }

    // ok and now to do the swaps, if there are any.
    if (*middle.begin() < *left.rbegin()) {
      auto nh1 = middle.extract(middle.begin());
      auto nh2 = left.extract(std::prev(left.end()));
      runningSum_ += nh2.value() - nh1.value();

      middle.insert(middle.begin(), std::move(nh2));
      left.insert(left.end(), std::move(nh1));
    }

    if (*right.begin() < *middle.rbegin()) {
      auto nh1 = middle.extract(std::prev(middle.end()));
      auto nh2 = right.extract(right.begin());
      runningSum_ -= nh1.value() - nh2.value();

      middle.insert(middle.end(), std::move(nh2));
      right.insert(right.begin(), std::move(nh1));
    }
  }

  int calculateMKAverage()
  {
    if (!ready_)
      return -1;

    return runningSum_ / (middleSize);
  }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
