#include <cstdio>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cinttypes>
#include <algorithm>
#include <memory>

// Because codeforces has a different view of this.
#define SCU "%" SCNu32 " "
#define SCD "%" SCNd64 " "
#define PRU "%" PRIu32
#define PRD "%" PRId64

/* using UT = std::uint64_t; */
using ST = std::int64_t;

using UT = std::uint32_t;                                                                                                                             
inline bool isBitSet(uint32_t num, uint32_t bit) {
        return ((num >> bit) & 1);
}

class Trie {
	private:
		struct Node {
			UT level{24};
			
			std::unique_ptr<Node> left{nullptr};
			std::unique_ptr<Node> right{nullptr};


			void insert(UT val) {
				if (this->level == 0)
					return;

				bool ss = isBitSet(val, this->level-1);
				if (ss) {
					if (!right) {
						right = std::make_unique<Node>();
						right->level = level-1;
					}
				
					/* printf("WE TOOK A RIGHT TURN\n"); */
					right->insert(val);
				} else {
					if (!left) {
						left = std::make_unique<Node>();
						left->level = level-1;
					}
					/* printf("WE TOOK A LEFT TURN\n"); */

					left->insert(val);
				}
			}

			UT findBest(UT maxVal, UT soFar) {
				if (level == 0) {
					/* printf(" WE ARE HERE " PRU "\n", soFar); */
					return soFar;
				}


				bool ss = isBitSet(maxVal, this->level-1);
				if (ss && left) {
					return left->findBest(maxVal, soFar<<1);
				} else {
					// Either the bit is not set, or left is not available.
					// We will go down both trees and see which one is better.
					if (left && right) {
					/* printf("WE ARE HERE\n"); */
						UT lans = left->findBest(maxVal, soFar<<1);
						UT rans = right->findBest(maxVal, (soFar<<1) | 1);

						UT lcal = (maxVal|lans) - lans;
						UT rcal = (maxVal|rans) - rans;

						if (lcal < rcal)
							return rans;
						else
							return lans;
					} else if (left) {
						return left->findBest(maxVal, soFar<<1);
					} else {
						// we know right atleast is set
						return right->findBest(maxVal, (soFar<<1) | 1);
					}
				}
			}
		};
	
		Node root;

	public:

		void insert(UT val) {
			root.insert(val);
		}

		UT findBest(UT maxVal) {
			/* printf("We are looking for the maximum for maxVal " PRU "\n", maxVal); */
			return root.findBest(maxVal, 0);
		}
};


int main() {
	UT T = 0;
	scanf(SCU, &T);
	for (UT t = 0; t < T; t++) {
		UT N = 0;
		UT Q = 0;
		scanf(SCU, &N);
		scanf(SCU, &Q);

		/* std::vector<UT> a; */
		Trie tr;

		UT lasti = 0;
		UT maxs = 0;
		for (UT i = 0; i < Q; i++) {
			UT ei = 0;
			scanf(SCU, &ei);
			const UT v = (ei + lasti) % N;
			tr.insert(v);
			/* printf("We have V: %" PRIu32 "\n", v); */

			/* a.push_back(v); */
			maxs = std::max(maxs, v);

			UT bst = tr.findBest(maxs);
			UT lastAns = (maxs|bst) - bst;
			/* printf("We got the answer " PRU " with best " PRU "\n", lastAns, bst); */
			printf(PRU " ", lastAns);

			lasti = lastAns;
			// The answer is always going to be 
		}
		printf("\n");

	}

	return 0;
}
