#include <iostream>
#include <numeric>
#include <queue>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MedianFinder
{

  std::priority_queue<int, std::vector<int>, std::ranges::less> leftSide;
  std::priority_queue<int, std::vector<int>, std::ranges::greater> rightSide;

public:
  void addNum(int num)
  {
    rightSide.emplace(num);

    while (!leftSide.empty() && !rightSide.empty() && rightSide.top() < leftSide.top()) {
      const auto la = leftSide.top();
      leftSide.pop();
      const auto ra = rightSide.top();
      rightSide.pop();

      leftSide.push(ra);
      rightSide.push(la);
    }

    while (leftSide.size() < rightSide.size()) {
      leftSide.push(rightSide.top());
      rightSide.pop();
    }
  }

  double findMedian()
  {
    if (leftSide.size() == rightSide.size()) {
      return std::midpoint<double>(leftSide.top(), rightSide.top());
    } else {
      return leftSide.top();
    }
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int
main()
{
  return 0;
}
