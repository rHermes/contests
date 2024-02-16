/**
* xorm - XOR Minimum
*
* My idea here, is to exploit the fact that XOR is Associatity.
*
* I'll build a tree of bits, and always try to go to 0, unless
* the current XOR stack is 1 for that bit.
*
* This way each query will execute in log2(32), and total
* runtime should be O(N)
*
* I realize now that this is some sort of trie, more specifically a bitwise trie.
* Due to the way I coded this, it ended up being quite slow compared to some
* other more compact solutions. I'll try to look into why that is.
*/

#include <cstdio>
#include <cstdint>
#include <memory>
#include <optional>


using UT = std::uint32_t;

inline bool isBitSet(uint32_t num, uint32_t bit) {
	return ((num >> bit) & 1);
}

class Tree {
private:
	struct Node {
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
	

		// In our case, this is the index of the original
		// number. We are storing the number itself in the
		// binary path to this node.
		std::optional<UT> value;

		
		// we add a number to the tree
		void add_number(const UT index, const UT val, const UT level) {
			if (level == 32) {
				if (!value)
					value = index;
				else
					value = std::min(index, *value);

				return;
			}

			const bool bitSet = isBitSet(val, 31-level);
			if (bitSet) {
				if (!right) this->right = std::make_unique<Node>();
				right->add_number(index, val, level+1);
			} else {
				if (!left) this->left = std::make_unique<Node>();
				left->add_number(index, val, level+1);
			}
		}

		[[nodiscard]] UT find_min_index(const UT xorm, const UT level) const {
			if (level == 32)
				return *value;

			const bool bitSet = isBitSet(xorm, 31-level);
			// If we have a bit here, we want to go right, as it would negate the
			// 1.
			if (bitSet) {
				if (right)
					return right->find_min_index(xorm, level+1);
				else
					return left->find_min_index(xorm, level+1);
			} else {
				if (left)
					return left->find_min_index(xorm, level+1);
				else
					return right->find_min_index(xorm, level+1);
			}
		}
	};

	Node root;

public:

	void add_number(const UT index, const UT val) {
		root.add_number(index, val, 0);
	}

	// We query the minimum given an XOR element
	[[nodiscard]] UT find_min_index(const UT xorm) const {
		return root.find_min_index(xorm, 0);
	}
};

int main() {
	UT N = 0;
	UT Q = 0;
	scanf("%u %u", &N, &Q);


	Tree tree;

	for (UT i = 0; i < N; i++) {
		UT x = 0;
		scanf("%u", &x);

		tree.add_number(i, x);
	}
	
	UT xorm = 0;
	for (UT i = 0; i < Q; i++) {
		UT x = 0;
		scanf("%u", &x);

		xorm ^= x;

		printf("%u\n", tree.find_min_index(xorm));
	}


	return 0;
}
