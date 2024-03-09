#include <iostream>
#include <vector>
#include <cinttypes>
#include <bit>
#include <cmath>


// This is for training on implementing the range minimum query for static data.
// I'll do this using multiple techniques.
using UT = std::uint64_t;
using ST = std::int64_t;

// A SqrtDecomp with a fixed BlockSize. Is most cases, this is going
// to be more efficient than the dynamic StaticSqrtDecomp
// 
template<typename IN, typename OUT, std::size_t BlockSize, typename F, OUT InitValue, typename DIFF_F = int>
class StaticSqrtDecomp {
	static_assert(std::is_same_v<DIFF_F, int> || std::is_invocable_r_v<OUT, DIFF_F, IN, IN>);

private:
	F func_{};
	DIFF_F diff_f{};

	std::vector<IN> orig_;
	std::vector<OUT> blocks_;


	void recompute() {
		blocks_.assign(orig_.size() / BlockSize + 1, InitValue);

		for (std::size_t i = 0; i < orig_.size(); i++) {
			blocks_[i / BlockSize] = func_(blocks_[i / BlockSize], orig_[i]);
		}
	}

public:

	explicit StaticSqrtDecomp(std::vector<IN>&& orig) : orig_{std::move(orig)} {
		recompute();
	}


	// This query is inclusive. It's [l,r].
	[[nodiscard]] OUT query(const std::size_t l, const std::size_t r) const {
		std::size_t start_block = l / BlockSize;
		std::size_t end_block = r / BlockSize;

		OUT ans = InitValue;

		if (start_block == end_block) {
			if (l % BlockSize == 0 && (r+1) % BlockSize == 0)
				ans = func_(ans, blocks_[start_block]);
			else {
				for (std::size_t c = l; c <= r; c++) {
					ans = func_(ans, orig_[c]);
				}
			}
		} else {
			// we check if our left value aligns perfectly with the start of the block.
			if (l % BlockSize == 0) {
				ans = func_(ans, blocks_[start_block]);
			} else {
				for (std::size_t cur = l; cur < (start_block+1)*BlockSize; cur++) {
					ans = func_(ans, orig_[cur]);
				}
			}
		
			// Check if we are right on the edge of a block.
			for (std::size_t cur_b = start_block+1; cur_b < end_block; cur_b++) {
				ans = func_(ans, blocks_[cur_b]);
			}

			if ((r+1) % BlockSize == 0) {
				ans = func_(ans, blocks_[end_block]);
			} else {
				for (std::size_t cur = end_block*BlockSize; cur <= r; cur++) {
					ans = func_(ans, orig_[cur]);
				}
			}
		}

		return ans;
	}

	void update(const std::size_t i, IN val) {
		const std::size_t block = i / BlockSize;
		if constexpr (std::is_invocable_r_v<OUT, DIFF_F, IN, IN>) {
			blocks_[block] += diff_f(orig_[i], val);
			orig_[i] = val;
		} else {
			orig_[i] = val;

			blocks_[block] = InitValue;
			for (std::size_t i = block*BlockSize; i < (block+1)*BlockSize; i++)
				blocks_[block] = func_(blocks_[block], orig_[i]);
		}
	}
};


void solveWithSqrtDecomp() {
	UT N = 0;
	UT Q = 0;
	std::cin >> N >> Q;

	std::vector<UT> in(N);
	for (UT i = 0; i < N; i++)
		std::cin >> in[i];

	auto f = [](UT a, UT b) { return a + b; };
	auto differ_f = [](UT oldv, UT newv) { return newv - oldv; };
	// We could get away with 448 here, but we choose 512, as it makes the compiler emit more
	// effective instructions.
	StaticSqrtDecomp<UT, UT, 512, decltype(f), 0, decltype(differ_f)> st(std::move(in));
	/* StaticSqrtDecomp<UT, UT, 512, decltype(f), 0> st(std::move(in)); */

	for (UT i = 0; i < Q; i++) {
		UT mode = 0;
		UT l = 0; 
		UT r = 0;
		std::cin >> mode >> l >> r;
		if (mode == 1) {
			st.update(l-1, r);
		} else {
			std::cout << st.query(l-1, r-1) << std::endl;
		}
	}
}

template<
	typename T,
	typename F,
	typename INV_F,
	T InitElement>
class BIT {
	static_assert(std::is_invocable_r_v<T, F, T, T>, "F needs to be a operator on the domain");
	static_assert(std::is_invocable_r_v<T, INV_F, T, T>, "INV_F needs to be an operator on the domain");
	private:
		F f_{};
		INV_F fi_{};

		std::vector<T> bit_;

	public:
		explicit BIT(std::size_t n) : bit_(n, InitElement) {}

		explicit BIT(const std::vector<T>& a) : BIT(a.size()) {
			for (std::size_t i = 0; i < a.size(); i++) {
				bit_[i] = f_(bit_[i], a[i]);
				std::size_t r = i | (i + 1);
				if (r < a.size())
					bit_[r] = f_(bit_[r], bit_[i]);
			}
		}

		void add(const std::size_t idx, const UT delta) {
			const auto N = bit_.size();

			// while we are less than N it's ok.
			for (std::size_t cur = idx; cur < N; cur = cur | (cur+1)) {
				bit_[cur] = f_(bit_[cur], delta);
			}
		}

		[[nodiscard]] T query(std::size_t r) const {
			T ret = InitElement;
			while (true) {
				ret = f_(ret, bit_[r]);

				r = r & (r+1);
				if (r == 0)
					break;

				r--;
			}

			return ret;
		}

		[[nodiscard]] T query(const std::size_t l, const std::size_t r) const {
			if (r < l)
				throw std::runtime_error("r < l is not allowed for query");

			if (l == 0)
				return query(r);
			else
				return fi_(query(r), query(l-1));
		}
};


void solveWithBIT() {
	UT N = 0;
	UT Q = 0;
	std::cin >> N >> Q;

	auto f = [](UT a, UT b) { return a + b; };
	auto f_inv = [](UT a, UT b) { return a - b; };
	BIT<UT, decltype(f), decltype(f_inv), 0> bit(N);

	std::vector<UT> vals(N);
	for (UT i = 0; i < N; i++) {
		std::cin >> vals[i];
		bit.add(i, vals[i]);
	}

	for (UT i = 0; i < Q; i++) {
		UT mode = 0;
		UT l = 0; 
		UT r = 0;
		std::cin >> mode >> l >> r;
		if (mode == 1) {
			bit.add(l-1, r - vals[l-1]);
			vals[l-1] = r;
		} else {
			std::cout << bit.query(l-1, r-1) << std::endl;
		}
	}
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	/* solveWithSqrtDecomp(); */
	solveWithBIT();

	return 0;
}
