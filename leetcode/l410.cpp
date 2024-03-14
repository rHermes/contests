#include <iostream>
#include <vector>
#include <cinttypes>

class Solution {
public:
	int splitArray(std::vector<int>& nums, int k) {
		std::vector<std::int64_t> psa(nums.size()+1);
		for (std::size_t i = 0; i < nums.size(); i++) {
			psa[i+1] = psa[i] + nums[i];
		}

		if (k == 1)
			return static_cast<int>(psa.back());

		// ok, now we can calculate the sumsum for all of them.
		//
		// Let's begin with the simplest case k=2
		//
		//  There are a couple of questions here:
		//  - Which of the subarrays will have the smallest sum?
		//  - How small is it?
		//
		//  Ok, but this is interesting. if we define that we
		//  never 
		//
		//  Could this potentially be a balance problem???
		//
		
		// OK, we might be able to do some DP here, with a double
		// setup.
		//
		// MinMaxBefore[L] the min maximum we can achive in [0, L-1]
		// MinMaxAfter[R]  the min maximum we can achieve in 

		// ok let's try this out then.

		// The DP is only ever interested in two things:
		//
		// Ok, let's try a self balancing act.
		std::vector<std::size_t> splits(static_cast<std::size_t>(k+1));
		// these two will never move, they just make the algorithm easier.
		splits.front() = 0;
		// The split is in front of the thing it guards.
		splits.back() = nums.size();

		for (std::size_t i = 1; i < splits.size()-1; i++) {
			splits[i] = i;
		}
		
		// the splits are stored as (prev, cur]
			// ok, now I want to balance these splits
			// . I will do that by always trying to balance the biggest

		// we establish a base answer.
		auto totsum = [&](std::size_t l, std::size_t r){
			return psa[r] - psa[l];
		};

		std::int64_t ans = 0;
		for (std::size_t i = 1; i < splits.size(); i++) {
			ans = std::max(ans, totsum(splits[i-1], splits[i]));
		}

		std::cout << "Our initial best effort is: " << ans << std::endl;
		std::cout << "Before this round of balancing: " << ans << std::endl;
		for (const auto& p : splits) {
			std::cout << p << " ";
		}
		std::cout << std::endl;

		while (true) {

			// we are now going to find the biggest element.
			// it might be worth it to go about this from the back, especially for longer setups
			/* for (std::size_t i = 1; i < splits.size(); i++) { */
			for (std::size_t i = splits.size()-2; 0 < i; i--) {
				/* const int64_t sum = totsum(splits[i-1], splits[i]); */
				if (splits[i]+1 == splits[i+1]) {
					continue;
				}

				const auto& pr = splits[i-1];
				auto& cur = splits[i];
				const auto& next = splits[i+1];
				
				// I'm sure I could create some sort of an binary search solution
				// here, as PSA is sorted.
				auto curWorst = std::max(totsum(pr,cur),totsum(cur,next));
				while (cur+1 < next) {
					// Now we must evaluate. What is the current worst?
					const auto nextWorst = std::max(totsum(pr,cur+1), totsum(cur+1,next));
					if (nextWorst < curWorst) {
						curWorst = nextWorst;
						cur++;
					} else {
						break;
					}
				}

				// Let's check if we can do better, by going forward.
				/* break; */
			}
			
			int64_t prev_best = ans;
			ans = 0;
			for (std::size_t i = 1; i < splits.size(); i++) {
				ans = std::max(ans, totsum(splits[i-1], splits[i]));
			}

			/* int biggest = -1; */
			std::cout << "After this round of balancing: " << ans << std::endl;
			for (const auto& p : splits) {
				std::cout << p << " ";
			}
			std::cout << std::endl;
			/* break; */

			if (ans == prev_best) {
				break;
			}
		}
		return static_cast<int>(ans);
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
	/* std::cout << s.splitArray(t1, 2) << std::endl; */
	/* std::cout << s.splitArray(t1, 3) << std::endl; */
	/* std::cout << s.splitArray(t2, 2) << std::endl; */
	/* std::cout << s.splitArray(t3, 2) << std::endl; */
	std::cout << s.splitArray(t4, 3) << std::endl;
	/* std::cout << s.splitArray(t4, 10) << std::endl; */
}
