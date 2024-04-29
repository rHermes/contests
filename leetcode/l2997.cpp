#include <bit>
#include <vector>
#include <iostream>
static auto _ = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	return nullptr;
}();


class Solution {
public:
    int minOperations(std::vector<int>& nums, int k) {
        // we want the total to be 0, because that would mean that the xor
        // of the nums would be 0.
        unsigned int ans = k;
        for (const auto num : nums)
            ans ^= num;
        
        // ok, now we know how many of these we have to flip.
        return std::popcount(ans);
    }
};

int main() { return 0; }
