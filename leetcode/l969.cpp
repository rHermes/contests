#include <algorithm>
#include <vector>
/* #include <random> */
/* #include <cmath> */
/* #include <chrono> */
/* #include <functional> */
/* #include <iostream> */

class Solution
{
public:
  static std::vector<int> pancakeSort(std::vector<int>& arr)
  {
    const int N = arr.size();

    std::vector<int> out;
    out.reserve(2 * N);

    for (int i = N - 1; 0 < i; i--) {
      if (arr[i] == i + 1)
        continue;

      auto it = std::find(arr.begin(), arr.begin() + i, i + 1);

      out.push_back(std::distance(arr.begin(), it) + 1);
      out.push_back(i + 1);

      std::reverse(arr.begin(), it + 1);
      std::reverse(arr.begin(), arr.begin() + i + 1);
    }

    return out;
  }
};

/* template<typename F> */
/* void performTest(F&& f) { */
/* 	std::ranlux48 gen(100); */

/* 	constexpr int TIMES = 1000; */
/* 	constexpr int SIZE = 1000; */

/* 	std::vector<int> input(SIZE); */
/* 	std::iota(input.begin(), input.end(), 1); */

/* 	std::vector<int> swaps; */
/* 	std::vector<double> times; */

/* 	for (int i = 0; i < TIMES; i++) { */
/* 		std::ranges::shuffle(input, gen); */
/* 		auto start = std::chrono::steady_clock::now(); */
/* 		auto res = std::invoke(f, input); */
/* 		std::chrono::duration<double, std::milli> dur = std::chrono::steady_clock::now() - start; */
/* 		times.push_back(dur.count()); */
/* 		swaps.push_back(res.size()); */
/* 	} */

/* 	double totalTimeSum = std::reduce(times.begin(), times.end()); */
/* 	double totalSwapSum = std::reduce(swaps.begin(), swaps.end()); */

/* 	const double avgTimeMs = totalTimeSum / TIMES; */
/* 	const double avgSwaps = totalSwapSum / TIMES; */

/* 	std::cout << "Average swaps: " << avgSwaps << ", average time spent: " << avgTimeMs << "ms\n"; */
/* } */

/* int main() { */
/* 	performTest(&Solution::pancakeSort); */
/* 	return 0; */
/* } */
