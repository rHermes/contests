/**
 * nwerc11c - ICPC NWERC 2011 C - Movie Collection
 *
 * I had to read the editorial here, and it turns out that the
 * answer to this is to use a something called a 
 * Fenwick/Binary Indexed Tree(BIT).
 *
 * We end up using two arrays here. One to keep track of where each
 * movie is in the BIT and a BIT to keep track of the prefix sums.
 *
 * When we start, we allocate a BIT with space for N movies, plus some
 * extra space. This extra space, is the number of queries we will do.
 *
 * The reason this is needed, is that every time a movie is queried,
 * we do the following:
 *
 * - Look up it's position in the BIT, through the array.
 * - Calculate the number of movies above it by doing a prefixSum on
 *   that position
 * - Decrease that position by 1 in the BIT
 * - Insert the movie at -1 or -2 or -3... depending on if it's the
 *   first, second or third movie to be queried.
 * - Update with the new position in the array
 * - Increase the position by 1 in the BIT
 *
 * This is the reason we need to allocate the extra space, so that
 * we can "insert" new movies.
 *
 * I think this was quite a cool task, and I learned about the 
 * Binary Indexed Tree. I've attached some good references below,
 * which I used to understand them. The first link is probably
 * the most important, as it allowed me to get an intuition
 * for the data structure.
 *
 * These strike me as a special case of the Segment Tree, which
 * I guess they are. The only difference here, is that
 * BITs require that their function is invertible, while segment
 * trees does not. This means that we can use operators like
 * "AND" with the segment tree, but not with a BIT.
 *
 * https://cs.stackexchange.com/a/10541
 * https://cp-algorithms.com/data_structures/fenwick.html#overview
 * https://www.nayuki.io/page/binary-indexed-tree
 * https://en.wikipedia.org/wiki/Fenwick_tree
 */

#include <cstdio>
#include <cstdint>

#include <vector>

using UT = std::uint32_t;
using ST = std::int32_t;

class BinaryIndexedTree {
	private:
		std::vector<ST> tree_;

		[[nodiscard]] inline ST getParent(ST index) const {
			return (index & (index + 1)) - 1;
		}

		[[nodiscard]] inline ST getNext(ST index) const {
			return index | (index + 1);
		}

	public:

		explicit BinaryIndexedTree(UT n) {
			tree_.resize(n);
		}

		void add(ST index, ST delta) {
			while (static_cast<UT>(index) < tree_.size()) {
				tree_[static_cast<UT>(index)] += delta;
				index = getNext(index);
			}
		}

		[[nodiscard]] ST prefixSum(ST index) const {
			ST ret = 0;

			while (0 <= index) {
				ret += tree_[static_cast<UT>(index)];
				index = getParent(index);
			}

			return ret;
		}
};

int main(void) {
	
	UT testcases;
	scanf("%u", &testcases);

	for (UT i = 0; i < testcases; i++) {
		UT N, M;
		scanf("%u %u", &N, &M);

		const UT extra_space =  M + 1;
		const ST extra_space_st = static_cast<ST>(extra_space);

		BinaryIndexedTree bit(N + extra_space);
		std::vector<ST> movies;
		for (UT j = 0; j < N; j++) {
			movies.emplace_back(j);
			// we add one
			bit.add(static_cast<ST>(extra_space + j), 1);
		}


		for (UT j = 0; j < M; j++) {
			UT id;
			scanf("%u", &id);
			id -= 1;

			// Figure out how many was there now:
			const ST before = bit.prefixSum(extra_space_st + movies[id]) - 1;
			// Decrease it
			bit.add(extra_space_st + movies[id], -1);
			// Set the new index
			movies[id] = -static_cast<ST>(j) - 1;
			
			// Update the new one
			bit.add(extra_space_st + movies[id], 1);

			if (j == 0) {
				printf("%u", before);
			} else {
				printf(" %u", before);
			}
		}
		printf("\n");
	}

	return 0;
}
