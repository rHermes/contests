#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MyQueue
{
  std::vector<int> intake;
  std::vector<int> outtake;

  void normalize()
  {
    if (!outtake.empty())
      return;

    while (!intake.empty()) {
      outtake.push_back(intake.back());
      intake.pop_back();
    }
  }

public:
  void push(int x) { intake.push_back(x); }

  int pop()
  {
    normalize();
    int ans = outtake.back();
    outtake.pop_back();
    return ans;
  }

  int peek()
  {
    normalize();
    return outtake.back();
  }

  bool empty() { return intake.empty() && outtake.empty(); }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
