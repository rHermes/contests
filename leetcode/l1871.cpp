#include <iostream>
#include <memory>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static bool canReach(const std::string& s, const int minJump, const int maxJump)
  {
    if (s.back() == '1')
      return false;

    // Ok, so we just need to keep a list of locations we can jump to?
    const int N = s.size();

    // Home made deque, to avoid overhead.
    auto Q = std::make_unique_for_overwrite<int[]>(N);
    int qL = 0;
    int qR = 0;

    const auto pushBack = [&](const int x) { Q[qR++] = x; };
    const auto popFront = [&]() { return Q[qL++]; };
    const auto isEmpty = [&]() { return qL == qR; };
    const auto getFront = [&]() { return Q[qL]; };
    const auto getBack = [&]() { return Q[qR - 1]; };

    pushBack(0);

    for (int i = 1; i < N; i++) {
      if (s[i] != '0')
        continue;

      while (!isEmpty() && getFront() < i - maxJump)
        popFront();

      if (isEmpty())
        return false;

      if (getFront() <= i - minJump) {
        pushBack(i);
      }
    }

    return (getBack() == N - 1);
  }
};
