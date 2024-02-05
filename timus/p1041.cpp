/**
 * p1041 - Nikifor
 *
 * So I actually solved this on my own, it's basically doing
 * a sort based on (cost, index) and incorporating it into a
 * gauss reduction. But the problem is that I'm getting some wrong
 * answers. There are so few ways to get info out of this judge,
 * so I don't know what the test cases are.
 *
 * I re implemented this in python, which has arbitrary length integers
 * and I get a timeout on a few test cases before mine, but this means that
 * it's probabily .
 *
 * So the solution here, is just to use a modulo and be very selective about
 * edge cases.
 *
 * I tried to implement this using my own fraction implementation, but there
 * must be some really nasty edge cases in the test cases, because it owerflows
 * on the later ones.
 */
#include <iostream>
#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <vector>
#include <algorithm>

constexpr std::uint64_t MOD_M = 10000019;

struct VectorElem {
	std::uint32_t index{0};
	std::uint32_t cost{0};

	// We also track the first pivot, to make sorting easier.
	std::uint32_t firstNonZero{0};

	std::vector<std::int64_t> elements;

	friend bool operator<(const VectorElem& l, const VectorElem& r) {
		return std::tie(l.firstNonZero, l.cost, l.index)
			< std::tie(r.firstNonZero, r.cost, r.index);
	}
};

inline std::uint64_t pmod(std::int64_t i, std::int64_t n) {
        return (i % n + n) % n;
}

std::uint64_t binPow(std::uint64_t a, std::uint64_t b, std::uint64_t m) {
	a %= m;
	std::uint64_t res = 1;
	while (0 < b) {
		if (b & 1)
			res = (res * a) % m;

		a = (a * a) % m;
		b >>= 1;
	}

	return res;
}


int main() {
	std::int32_t M = 0;
	std::int32_t N = 0;

	std::cin >> M >> N;
	std::vector<VectorElem> vecs;
	
	// Parse the vectors
	for (std::int32_t i = 1; i <= M; i++) {
		VectorElem vec;
		vec.index = i;
		vec.firstNonZero = N;

		bool foundFirstNonZero = false;
		for (std::int32_t col = 0; col < N; col++) {
			std::int32_t x = 0;
			std::cin >> x;


			if (!foundFirstNonZero && x != 0) {
				foundFirstNonZero = true;
				vec.firstNonZero = col;
			}

			auto up = pmod(x, MOD_M);
			vec.elements.emplace_back(up);
		}

		vecs.push_back(vec);
	}
	
	// Get the cost 
	for (std::int32_t i = 0; i < M; i++) {
		std::cin >> vecs[i].cost;
	}
	
	// We sort the vectors to get a good starting point.
	std::sort(vecs.begin(), vecs.end());

	/* for (const auto& v : vecs) { */
	/* 	std::cout << "IDX: " << v.index << ", COST: " << v.cost << ", PIV: " << v.firstNonZero; */
	/* 	std::cout << " ["; */
	/* 	for (const auto& x : v.elements) { */
	/* 		std::cout << x << ", "; */
	/* 	} */
	/* 	std::cout << "]"; */
	/* 	std::cout << std::endl; */
	/* } */


	for (std::int32_t row = 0; row < N; row++) {
		// We always begin with asserting that we can even complete the test.
		// If we don't have N linearly independent vectors in the whole set,
		// we can never complete the task, and we exit early.
		if (vecs[row].firstNonZero != row) {
			std::cout << "0" << std::endl;
			return 0;
		}

		const auto nextRowIt = std::next(vecs.begin(), row+1);

		// We now pick out our pivot.
		auto pivValue = vecs[row].elements[row];
		if (pivValue != 1) {
			auto revFactor = binPow(pivValue, MOD_M-2, MOD_M);
			for (std::int32_t col = row; col < N; col++) {
				vecs[row].elements[col] *= revFactor;
				vecs[row].elements[col] = pmod(vecs[row].elements[col], MOD_M);
			}
		}

		// We will remove this from all vectors below.
		for (auto it = nextRowIt; it != vecs.end(); it++) {
			const auto firstElem = it->elements[row];
			if (firstElem == 0)
				continue;


			// subtract it from the row
			for (std::int32_t col = row; col < N; col++) {
				/* it->elements[col] -= scaleFactor * vecs[row].elements[col]; */
				it->elements[col] -= firstElem * vecs[row].elements[col];
				it->elements[col] = pmod(it->elements[col], MOD_M);
			}

			// we need to update the first non zero row now.
			it->firstNonZero = N;
			for (std::int32_t col = row+1; col < N; col++) {
				if (it->elements[col] != 0) {
					it->firstNonZero = col;
					break;
				}
			}
		}


		// we now need to sort all rows below this one, as we may have changed them.
		std::sort(nextRowIt, vecs.end());
	}


	std::uint64_t ans = 0;
	std::vector<std::uint32_t> used;
	for (std::int32_t row = 0; row < N; row++) {
		ans += vecs[row].cost;
		used.push_back(vecs[row].index);
	}
	std::cout << ans << std::endl;

	std::sort(used.begin(), used.end());
	for (const auto& idx : used)
		std::cout << idx << std::endl;

	return 0;
}

