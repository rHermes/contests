#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT C = 0;
	std::cin >> N >> C;


	// Let's try this the other way.
	// How many total pairs are there?
	const UT totalPairs = ((C+1)*(C+2))/2;

	// We take away the count of x + y
	UT invalidOne = 0;
	UT invalidTwo = 0;
	UT evens = 0;

	for (UT i = 0; i < N; i++) {
		UT s = 0;
		std::cin >> s;

		invalidOne += s/2 + 1;
		invalidTwo += C - s + 1;

		if (s % 2 == 0)
			evens++;
	}

	UT odds = N - evens;

	// Now this is where the sauce realllllyyyyy gets made.
	// So we set up
	// x + y = si
	// y - x = sj
	//
	// Solving for X:
	// y = sj + x
	//
	// x + sj + x = si
	// x = (si-sj)/2
	//
	// Solving for Y:
	//
	// (si-sj)/2 + y = si
	// y = si - (si-sj)/2
	// y = (2*si - si + sj)/2
	// y = (si + sj)/2
	//
	// So we have then:
	// x = (si - sj)/2
	// y = (si + sj)/2
	//
	// As x and y are integers, both of these two values must be even and both must positive.
	//
	// so we have 
	//
	// sj <= si
	//
	// And since they are integers, we can see that it must be an (even + even => even) or
	// (odd + odd => even), since (odd + even => odd). So now we just need the number of
	// ways we can have
	//
	// sj <= si
	// sj and si have the same parity.
	//
	// This is just the number of ways to combine the even or odd numbers in our array, when
	// order doesn't matter. This is the same as we did above, and so we are just summing the
	// number of evens and odds in our array.

	UT doubleCount = (evens*(evens+1))/2 + (odds*(odds+1))/2;

	std::cout << totalPairs - invalidOne - invalidTwo + doubleCount << std::endl;
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
