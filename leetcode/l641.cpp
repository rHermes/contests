#include <iostream>
#include <memory>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MyCircularDeque
{
  std::size_t cap_;
  std::size_t head_{ 0 };
  std::size_t tail_{ 0 };
  std::unique_ptr<int[]> data_{ std::make_unique_for_overwrite<int[]>(cap_ + 1) };

  [[nodiscard]] constexpr std::size_t nextIdx(const std::size_t idx) const { return (idx != cap_) ? (idx + 1) : 0; }

  [[nodiscard]] constexpr std::size_t prevIdx(const std::size_t idx) const { return (idx != 0) ? (idx - 1) : cap_; }

public:
  constexpr MyCircularDeque(int k) : cap_{ static_cast<std::size_t>(k) } {}

  constexpr bool insertFront(int value)
  {
    if (isFull())
      return false;

    head_ = prevIdx(head_);
    data_[head_] = value;

    return true;
  }

  constexpr bool insertLast(int value)
  {
    if (isFull())
      return false;

    data_[tail_] = value;
    tail_ = nextIdx(tail_);
    return true;
  }

  constexpr bool deleteFront()
  {
    if (isEmpty()) {
      return false;
    }

    // What this would do in real life to free the resource
    // std::ranges::destroy_at(&(data_[head_]));

    head_ = nextIdx(head_);
    return true;
  }

  constexpr bool deleteLast()
  {
    if (isEmpty())
      return false;

    tail_ = prevIdx(tail_);

    // What we would do in real life to release the resource.
    // std::ranges::destroy_at(&data_[tail_]);
    return true;
  }

  [[nodiscard]] constexpr int getFront() const
  {
    if (isEmpty())
      return -1;

    return data_[head_];
  }

  [[nodiscard]] constexpr int getRear() const
  {
    if (isEmpty())
      return -1;

    return data_[prevIdx(tail_)];
  }

  [[nodiscard]] constexpr bool isEmpty() const { return head_ == tail_; }

  [[nodiscard]] constexpr bool isFull() const { return head_ == nextIdx(tail_); }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
