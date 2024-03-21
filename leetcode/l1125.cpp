#include <bitset>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstddef>


class Solution {
	public:
		std::vector<int> smallestSufficientTeam(std::vector<std::string>& req_skills,
				std::vector<std::vector<std::string>>& people) {
			std::bitset<16> required;
			std::unordered_map<std::string, std::bitset<16>> skills;
			for (std::size_t i = 0; i < req_skills.size(); i++) {
				skills[req_skills[i]].set(i);
				required.set(i);
			}

			// ok now we have what we need.
			// Now we are going to create the other bitsets
			std::vector<std::bitset<16>> sack(people.size());
			for (std::size_t i = 0; i < people.size(); i++) {
				for (const auto& s : people[i])
					sack[i] |= skills[s];
			}

			// The DP is a mapping between a current skills coverage,
			// and the minimal number of people we need to fullfill it.
			std::vector<std::bitset<60>> dp(1 << req_skills.size());

			// What we will do now, is that we will calculate this for each possible
			// skill mask. It's simply the smallest peoples mask, when we add another
			// worker.
			for (std::size_t i = 1; i < dp.size(); i++) {
				const std::bitset<16> skillsMask(i);
				std::bitset<60> best;
				best.set();

				for (std::size_t j = 0; j < sack.size(); j++) {
					auto smallerSkillMask = skillsMask & ~sack[j];
					if (smallerSkillMask == skillsMask)
						continue;

					auto peopleMask = dp[smallerSkillMask.to_ulong()];
					peopleMask.set(j);
					if (peopleMask.count() < best.count())
						best = peopleMask;
				}

				dp[i] = best;
			}

			// Now the answer must be in the ans
			std::vector<int> ans;
			for (std::size_t i = 0; i < people.size(); i++) {
				if (dp.back()[i])
					ans.push_back(static_cast<int>(i));
			}
			return ans;
		}
};

int main() { return 0; }
