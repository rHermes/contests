#include <iostream>
#include <vector>
inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MinStack
{
  // val, min below me.
  std::vector<std::pair<int, int>> stack;

public:
  void push(int val)
  {
    if (stack.empty()) {
      stack.emplace_back(val, val);
    } else {
      stack.emplace_back(val, std::min(val, stack.back().second));
    }
  }

  void pop() { stack.pop_back(); }

  int top() { return stack.back().first; }

  int getMin() { return stack.back().second; }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
