#include <algorithm>
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
  static void nextPermutation(std::vector<int>& nums) { 
		std::ranges::next_permutation(nums); 
	}
};
