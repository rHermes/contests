#include <iostream>
#include <vector>
#include <cinttypes>
#include <algorithm>

class Solution {
public:
	[[nodiscard]] static constexpr bool canBeDone(
			const std::vector<std::int64_t>& psa, const std::size_t k, const std::int64_t target) {
		if (target < psa.front())
			return false;

		std::size_t buckets = 1;
		auto it = std::upper_bound(psa.cbegin(), psa.cend(), target);
		while (it != psa.cend()) {
			buckets++;
			if (k < buckets)
				return false;
			
			it = std::upper_bound(it, psa.cend(), *(it-1) + target);
		}

		return true;
	}

	int splitArray(std::vector<int>& nums, int k) {
		std::vector<std::int64_t> psa(nums.size());
		psa[0] = nums[0];
		std::int64_t lowerBound = 0;
		for (std::size_t i = 1; i < nums.size(); i++) {
			psa[i] = psa[i-1] + nums[i];
			lowerBound = std::max(lowerBound, static_cast<std::int64_t>(nums[i]));
		}
		if (lowerBound == 0)
			return 0;

		if (k == 1)
			return static_cast<int>(psa.back());


		std::int64_t upperBound = psa.back();
		lowerBound--;
		
		while (lowerBound+1 < upperBound) {
			const auto mid = (lowerBound+upperBound)/2;
	
			if (canBeDone(psa, static_cast<std::size_t>(k), mid)) {
				upperBound = mid;
			} else {
				lowerBound = mid;
			}
		}


		return static_cast<int>(upperBound);
	}
};

int main() {
	// [7,2,5,10,8] k=2, ans = 18
	// nums = [1,2,3,4,5], k = 2, output = 9
	Solution s;
	std::vector<int> t1 = {7, 2, 5, 10, 8};
	std::vector<int> t2 = {1, 2, 3, 4, 5};
	std::vector<int> t3 = {1, 1, 1, 1, 1};
	std::vector<int> t4 = {1, 2, 1, 1, 1, 10, 23, 1, 100, 42, 42, 1, 1, 1, 1, 1, 1};
	std::vector<int> t5 = {10,5,13,4,8,4,5,11,14,9,16,10,20,8};
	std::vector<int> t6 = {0, 0, 0, 0, 0};
	/* std::cout << s.splitArray(t1, 2) << std::endl; */
	/* std::cout << s.splitArray(t1, 3) << std::endl; */
	/* std::cout << s.splitArray(t2, 2) << std::endl; */
	/* std::cout << s.splitArray(t3, 2) << std::endl; */
	/* std::cout << s.splitArray(t4, 3) << std::endl; */
	std::cout << s.splitArray(t5, 4) << std::endl;
	/* std::cout << s.splitArray(t4, 10) << std::endl; */
	std::cout << s.splitArray(t6, 3) << std::endl;
}
