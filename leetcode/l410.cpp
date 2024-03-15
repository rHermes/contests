#include <iostream>
#include <vector>
#include <cinttypes>
#include <algorithm>

class Solution {
public:
	static void optimizeArray(const std::vector<std::int64_t>& psa, std::vector<std::size_t>& splits) {
		// we establish a base answer.
		auto totsum = [&](std::size_t l, std::size_t r){
			return psa[r] - psa[l];
		};

		bool changed = true;
		while (changed) {
			changed = false;
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
					if (nextWorst <= curWorst) {
						curWorst = nextWorst;
						cur++;
						changed = true;
					} else {
						break;
					}
				}

				// Let's check if we can do better, by going forward.
				/* break; */
			}
			
			/* ans = 0; */
			/* for (std::size_t i = 1; i < splits.size(); i++) { */
			/* 	ans = std::max(ans, totsum(splits[i-1], splits[i])); */
			/* } */

			/* int biggest = -1; */
			/* std::cout << "After this round of balancing: " << ans << std::endl; */
			for (std::size_t i = 1; i < splits.size(); i++) {
				std::cout << splits[i] << ": " << totsum(splits[i-1], splits[i]) << std::endl;
				/* ans = std::max(ans, totsum(splits[i-1], splits[i])); */
			}
			std::cout << std::endl;
		}
	}

	static void optimizeArray2(const std::vector<std::int64_t>& psa, std::vector<std::size_t>& splits) {
		// we establish a base answer.
		auto totsum = [&](std::size_t l, std::size_t r){
			return psa[r] - psa[l];
		};
		// Ok, so here is our new strategy. We will loop until we can no longer improve the array.
		// There are two ways we can do this. The first is that we can spread the ticks out, like we
		// did above.
		// The second we can do, is to move a tick from one spot, over the others.
		//
		// By combining the two, I think this can be pretty rad.
	   

		// we find the current maximum

		while (true) {
			std::int64_t maxSeg = -1;
			std::size_t posMax = 0;
			for (std::size_t i = 1; i < splits.size(); i++) {
				const auto segSum = totsum(splits[i-1], splits[i]);
				if (maxSeg < segSum) {
					maxSeg = segSum;
					posMax = i;
				}
			}

			// If the maximum is squashed between two numbers, we are never getting it out.
			if (splits[posMax-1]+1 == splits[posMax])
				return;

			// Ok, now we are going to see if there are any any numbers, who has a total span width
			// less than the max length. If there is, then we know that we can actually move that pin
			// into the best spot. There is no need to do this optimally, the algorithm will simply
			// balance these things out. The only bad option here would be if there is only 1 stopper,
			// in which case we could not balance these out. Calling the other optimize first, which
			// gives a rough estimation aught to be enought ot get things rolling.
			std::size_t midNode = 0;
			for (std::size_t i = 1; i < splits.size()-1; i++) {
				if (totsum(splits[i-1], splits[i+1]) < maxSeg) {
					midNode = i;
				}
			}

			if (midNode == 0)
				break;


			std::cout << "we are going to be replacing node: " << splits[midNode] << " and putting it between " <<
				splits[posMax-1] << " and " << splits[posMax] << std::endl;
				/* splits[posi-1] << */
		

			const auto& prev = splits[posMax-1];
			auto curPos = prev+1;
			const auto& next = splits[posMax];

			//ok, we are going to see what we can do now.
			//
			auto curWorst = std::max(totsum(prev,curPos),totsum(curPos,next));
			while (curPos+1 < next) {
				// Now we must evaluate. What is the current worst?
				const auto nextWorst = std::max(totsum(prev,curPos+1), totsum(curPos+1,next));
				if (nextWorst < curWorst) {
					curWorst = nextWorst;
					curPos++;
					/* changed = true; */
				} else {
					break;
				}
			}
			
			// assign the new value.
			splits[midNode] = curPos;

			// We have to do this, as we have shifted around the array members.
			std::sort(splits.begin(), splits.end());

			for (std::size_t i = 1; i < splits.size(); i++) {
				std::cout << splits[i] << ": " << totsum(splits[i-1], splits[i]) << std::endl;
				/* ans = std::max(ans, totsum(splits[i-1], splits[i])); */
			}
		}
	}

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

		// OK, so what we can do now. Is we can 
		
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

		optimizeArray2(psa, splits);
		optimizeArray(psa, splits);


		ans = 0;
		for (std::size_t i = 1; i < splits.size(); i++) {
			ans = std::max(ans, totsum(splits[i-1], splits[i]));
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
	std::vector<int> t5 = {10,5,13,4,8,4,5,11,14,9,16,10,20,8};
	/* std::cout << s.splitArray(t1, 2) << std::endl; */
	/* std::cout << s.splitArray(t1, 3) << std::endl; */
	/* std::cout << s.splitArray(t2, 2) << std::endl; */
	/* std::cout << s.splitArray(t3, 2) << std::endl; */
	/* std::cout << s.splitArray(t4, 3) << std::endl; */
	std::cout << s.splitArray(t5, 8) << std::endl;
	/* std::cout << s.splitArray(t4, 10) << std::endl; */
}
