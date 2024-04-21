#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

class Solution {
public:
	static constexpr std::size_t MAXN = 2 * 10000;
	std::array<std::uint16_t, MAXN + 1> cnt;

	int atMostK(int k, const std::vector<int>& nums) {
		int answer = 0;
		// we reset the array, between each run.
		cnt.fill(0);

		// first we move all the way until we have k unique elements.
		std::size_t l = 0;
		std::size_t r = 0;
		for (; r < nums.size(); r++) {
			if (cnt[nums[r]]++ == 0)
				k--;

			if (k < 0)
				break;

			answer += r + 1;
		}

		if (0 <= k) {
			return answer;
		}
		// now we just need to adust l, and we are golden.
		while (--cnt[nums[l++]] != 0);

		answer += r - l + 1;

		// now we do the normal loop:
		r++;
		for (; r < nums.size(); r++) {
			if (cnt[nums[r]]++ == 0) {
				while (--cnt[nums[l++]] != 0);
			}

			answer += r - l + 1;
		}

		return answer;
	}

	int subarraysWithKDistinct(std::vector<int>& nums, int k) {
		return atMostK(k, nums) - atMostK(k - 1, nums);
	}
};

auto init = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	return 'c';
}();

int main() { return 0; }
