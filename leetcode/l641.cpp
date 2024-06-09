#include <cstdint>
#include <vector>

class MyCircularDeque
{
  std::size_t cap_;
  std::size_t head_{ 0 };
  std::size_t tail_{ 0 };
  std::vector<int> data_;

public:
  MyCircularDeque(int k) : cap_{ static_cast<std::size_t>(k) + 1 }, data_(cap_) {}

  bool insertFront(int value)
  {
    if (isFull())
      return false;

    head_ = (head_ + cap_ - 1) % cap_;
    data_[head_] = value;

    return true;
  }

  bool insertLast(int value)
  {
    if (isFull())
      return false;

    data_[tail_] = value;
    tail_ = (tail_ + 1) % cap_;
    return true;
  }

  bool deleteFront()
  {
    if (isEmpty()) {
      return false;
    }

    head_ = (head_ + 1) % cap_;
    return true;
  }

  bool deleteLast()
  {
    if (isEmpty())
      return false;

    tail_ = (tail_ + cap_ - 1) % cap_;
    return true;
  }

  int getFront()
  {
    if (isEmpty())
      return -1;

    return data_[head_];
  }

  int getRear()
  {
    if (isEmpty())
      return -1;

    return data_[(tail_ + cap_ - 1) % cap_];
  }

  bool isEmpty() { return head_ == tail_; }

  bool isFull() { return ((tail_ + 1) % cap_) == head_; }
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
