#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static bool validateStackSequences(const std::vector<int>& pushed, const std::vector<int>& popped)
  {

    const int N = pushed.size();
    std::vector<int> stack;
    stack.reserve(N);

    int inIdx = 0;
    for (int i = 0; i < N; i++) {
      while (inIdx < N && (stack.empty() || stack.back() != popped[i])) {
        stack.push_back(pushed[inIdx++]);
      }

      if (stack.empty() || stack.back() != popped[i])
        return false;

      stack.pop_back();
    }

    return true;
  }
};
