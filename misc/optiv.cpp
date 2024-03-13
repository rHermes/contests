// https://leetcode.com/discuss/interview-question/2730450/Optiver-Online-Assessment-2022
#include <cmath>
#include <iostream>
#include <cinttypes>
#include <memory>
#include <vector>

using UT = std::uint64_t;

template <typename T>
class SegTree {
	public:
    using in_t = std::conditional_t<std::is_arithmetic_v<T>, T, T&>;

	private:
	struct Node {
		T val{0};
		T diff{0};
	};

	const std::size_t N_;
	std::unique_ptr<Node[]> data_;

	constexpr void push_down(const std::size_t idx) {
		auto &root = data_[idx];
		if (root.diff != 0) {
			auto& left = data_[2*idx];
			auto& right = data_[2*idx+1];
		
			// Add the diff to the two children.
			left.diff += root.diff;
			right.diff += root.diff;
			
			// Ok, now we update the root value and we reset the diff.
			root.val += root.diff;
			root.diff = 0;
		}
	}

	constexpr void update(const std::size_t idx, const std::size_t tl, const std::size_t tr,
						const std::size_t L, const std::size_t R, const in_t delta) {
		if (tl == L && tr == R)  {
			// we have a match, we update the diff, as we are doing this update lazily.
			data_[idx].diff += delta;
			return;
		} else {
			const auto tm = (tl+tr)/2;

			// Since this was a miss, it means that the node will have always add this value to its
			// total value, so we do that now.
			data_[idx].val += delta;
	
			// Should we recurse into the left subtree?
			if (L <= tm) {
				update(2*idx, tl, tm, L, std::min(tm,R), delta);
			}

			// Should we recurse into the right subtree?
			if (tm+1 <= R) {
				update(2*idx + 1, tm+1, tr, std::max(tm+1,L), R, delta);
			}
		}
	}

	[[nodiscard]] constexpr T query(const std::size_t idx, const std::size_t tl, const std::size_t tr,
						const std::size_t L, const std::size_t R) {
		if (tl == L && tr == R)  {
			return data_[idx].val + data_[idx].diff;
		} else {
			// Before anything, we need to propagate lazy changes.
			push_down(idx);
			const auto tm = (tl+tr)/2;

			T ans = 0;
	
			// Should we recurse into the left subtree?
			if (L <= tm) {
				ans += query(2*idx, tl, tm, L, std::min(tm,R));
			}

			// Should we recurse into the right subtree?
			if (tm+1 <= R) {
				ans += query(2*idx + 1, tm+1, tr, std::max(tm+1,L), R);
			}

			return ans;
		}
	}

	void printOut(const std::size_t idx, const std::size_t tl, const std::size_t tr, const std::size_t level) {
		for (UT i = 0; i < level; i++) {
			std::cout << "  ";
		}
		const auto& node = data_[idx];
		std::cout << "[" << tl << ", " << tr << "]: diff=" << node.diff << ", val=" << node.val << std::endl;
		if (tl == tr || (node.diff == 0 && node.val == 0)) {
			return;
		}
		const auto tm = (tl+tr)/2;
		printOut(2*idx, tl, tm, level+1);
		printOut(2*idx + 1, tm+1, tr, level+1);
	}


public:
	constexpr explicit SegTree(std::size_t N) : N_{N}, data_{std::make_unique<Node[]>(4*(N_+1))} {}

	constexpr void update(const std::size_t l, const std::size_t r, const in_t delta) {
		update(1, 0, N_, l, r, delta);
	}


	[[nodiscard]] constexpr T get(const std::size_t day) {
		return query(1, 0, N_, day, day);
	}

	void printTree() {
		printOut(1, 0, N_, 0);
	}

};


// Fenwick tree.
template <typename T>
class BIT {
	using in_t = std::conditional_t<std::is_arithmetic_v<T>, T, T&>;

	const std::size_t N_;
	std::unique_ptr<T[]> data_;


	public:
	constexpr explicit BIT(std::size_t n) : N_{n}, data_{std::make_unique<T[]>(N_)} {}

	constexpr explicit BIT(const std::vector<T>& inp) : BIT(inp.size()) {
		for (std::size_t i = 0; i < N_; i++) {
			data_[i] += inp[i];
			auto r = i | (i+1);
			if (r < N_)
				data_[r] += data_[i];
		}
	}

	constexpr void add(std::size_t idx, const in_t delta) {
		for (; idx < N_; idx = idx | (idx+1))
			data_[idx] += delta;
	}

	[[nodiscard]] constexpr T sum(std::size_t idx) {
		T ans = data_[idx];
		idx = idx & (idx + 1);
		while (0 < idx) {
			idx--;
			ans += data_[idx];
			idx = idx & (idx + 1);
		}
		return ans;
	}

	[[nodiscard]] constexpr T sum(std::size_t l, std::size_t r) {
		if (l == 0)
			return sum(r);
		else
			return sum(r) - sum(l-1);
	}

};

/* #define USE_SEG */
constexpr std::size_t MAXD = 1000000;

int main() {
	std::cin.exceptions(std::ios_base::failbit);

	UT S = 0;
	UT N = 0;
	std::cin >> S >> N;

#ifndef USE_SEG
	BIT<UT> bit(MAXD+1);
	bit.add(0, S);
#else
	SegTree<UT> tree{MAXD};
	tree.update(0, MAXD, S);
#endif

	std::vector<std::pair<UT,UT>> divs(N);
	for (UT i = 0; i < N; i++) {
		auto& [a, d]= divs[i];
		std::cin >> a >> d;
#ifndef USE_SEG
		bit.add(d, -a);
#else
		// Decrement that ranges values.
		tree.update(d, MAXD, -a);
#endif
	}
	
	UT Q = 0;
	std::cin >> Q;
	for (UT q = 0; q < Q; q++) {
		UT typ = 0;
		std::cin >> typ;
		if (typ == 1) {
			UT i = 0;
			UT a = 0;
			UT d = 0;
			std::cin >> i >> a >> d;

			// first we remove old range, and then add the new
			auto& [oldA, oldD] = divs[i-1];
#ifndef USE_SEG
			bit.add(oldD, oldA);
			bit.add(d, -a);
#else
			tree.update(oldD, MAXD, oldA);
			tree.update(d, MAXD, -a);
#endif
			oldA = a;
			oldD = d;
		} else if (typ == 2) {
			UT f = 0;
			std::cin >> f;
#ifndef USE_SEG
			std::cout << bit.sum(f) << std::endl;
#else
			std::cout << tree.get(f) << std::endl;
#endif
		} else {
			throw std::runtime_error("Wrong query type");
		}
	}

	return 0;
}
