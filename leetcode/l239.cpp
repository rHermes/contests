#include <iostream>
#include <vector>
#include <stack>
#include <utility>

inline const auto optimize = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	return 0;
}();


class Solution {
public:
	std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
		std::stack<std::pair<int, int>> s1;
		std::stack<std::pair<int, int>> s2;

		const auto pushElem = [&](int x) {
			if (s1.empty()) {
				s1.emplace(x, x);
			} else {
				s1.emplace(x, std::max(x, s1.top().second));
			}
		};

		const auto getMax = [&] {
			if (s1.empty()) {
				return s2.top().second;
			} else if (s2.empty()) {
				return s1.top().second;
			} else {
				return std::max(s1.top().second, s2.top().second);
			}
		};

		const auto popElem = [&] {
			if (s2.empty()) {
				while (!s1.empty()) {
					const auto elem = s1.top().first;
					s1.pop();

					const auto maxi = s2.empty() ? elem : std::max(elem, s2.top().second);
					s2.emplace(elem, maxi);
				}
			}

			s2.pop();
		};

		std::size_t i = 0;
		for (; i < static_cast<std::size_t>(k); i++) {
			pushElem(nums[i]);
		}

		nums[0] = getMax();
		for (; i < nums.size(); i++) {
			popElem();
			pushElem(nums[i]);
			nums[i-k+1] = getMax();
		}

		nums.resize(nums.size()-k+1);

		return nums;
	}
};

int main() { return 0; }
