#include <iostream>
#include <map>
#include <set>
/* #include <memory_resource> */
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <deque>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT K = 0;
	std::cin >> N >> K;

	// We can always makes cliques of up to K elements, so the number of cliques is
	// std::ceil(N/K). The way we generate them is by putting the middle elements on
	// the side and then going decreasing from the left and increasing from the right.
	// The reason for this is that 1 and K, must always be right next to each other.
	// The rest of the pattern is intuitive, but I also brute forced it in python once
	// I got the idea.
	

	const auto timesFull = N / K;
	const auto timesHalf = N % K;
	
	// How many times we
	const auto split = K/2;

	UT cur = 1;
	std::vector<UT> ans;

	for (UT i = 0; i < timesFull; i++) {
		UT j = 0;
		for (; j < split; j++)
			ans.push_back(cur + (split-j) - 1);

		for (; j < K; j++)
			ans.push_back(cur + K - j + split - 1);
		
		cur += K;
	}
	
	// Now it's just the same, except we are just going to go until the end.
	if (timesHalf) {
		/* ans.push_back(100); */
		const auto lsplit = timesHalf / 2;
		UT j = 0;
		for (; j < lsplit; j++)
			ans.push_back(cur + (lsplit-j) - 1);

		for (; j < timesHalf; j++)
			ans.push_back(cur + timesHalf - j + lsplit - 1);

		cur += K;
	}

	for (const auto& p : ans)
		std::cout << p << " ";

	std::cout << std::endl;
	std::cout << timesFull + (timesHalf != 0) << std::endl;

	UT cnt = 1;
	for (UT i = 0; i < timesFull; i++) {
		for (UT k = 0; k < K; k++)
			std::cout << cnt << " ";

		cnt++;
	}

	for (UT k = 0; k < timesHalf; k++)
		std::cout << cnt << " ";

	cnt++;
	std::cout << std::endl;
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
