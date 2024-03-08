#include <iostream>
#include <vector>
#include <cinttypes>
#include <bit>
#include <cmath>


// This is for training on implementing the range minimum query for static data.
// I'll do this using multiple techniques.
using UT = std::uint64_t;
using ST = std::int64_t;

template <typename T>
class Vector2D {
	private:
	std::size_t rows_{0};
	std::size_t cols_{0};
	std::vector<T> data_;

	public:

	Vector2D(std::size_t rows, std::size_t cols) : rows_{rows}, cols_{cols}, data_(rows_*cols_) {}

	Vector2D(const Vector2D& other) : 
		rows_{other.rows_} , cols_{other.cols_}
	, data_{other.data_}
	{}

	Vector2D(Vector2D&& other) noexcept : 
		rows_{other.rows_} , cols_{other.cols_}
	, data_{std::move(other.data_)}
	{}

	Vector2D& operator=(const Vector2D& other) {
		*this = Vector2D(other);
		return *this;
	}

	Vector2D& operator=(Vector2D&& other) noexcept {
		rows_ = other.rows_;
		cols_ = other.cols_;
		data_ = std::move(other.data_);
		return *this;
	}

	[[nodiscard]] std::size_t idx(std::size_t row, std::size_t col) const {
		return row*cols_ + col;
	}

	[[nodiscard]] const T& get(std::size_t row, std::size_t col) const {
		return data_[idx(row, col)];
	}

	[[nodiscard]] T& get(std::size_t row, std::size_t col) {
		return data_[idx(row, col)];
	}

	[[nodiscard]] T* data() noexcept {
		return data_.data();
	}

	[[nodiscard]] const T* data() const {
		return data_.data();
	}
};

template <typename T, typename F, bool IDEMPOTENT = false>
class SparseTable {
	F func_{};
	const std::size_t maxN_;
	const std::size_t maxK_{static_cast<std::size_t>(std::bit_width(maxN_)-1)};

	Vector2D<T> data_{maxK_+1, maxN_+1};

public:

	explicit SparseTable(std::size_t maxN) : maxN_{maxN} {}
	SparseTable(F fn, std::size_t maxN) : func_{fn},  maxN_{maxN} {}
	
	template <typename IT>
	void precompute(IT first, IT last) {
		// This is a bit dirty, but we know the internals of the 2D data.
		std::copy(first, last, data_.data());

		for (std::size_t i = 1; i <= maxK_; i++) {
			for (std::size_t j = 0; j + (1 << i) <= maxN_; j++) {
				data_.get(i, j) = func_(
						data_.get(i-1, j), // range [j, j + 2^(i-1) -1]
						data_.get(i-1, j + (1 << (i -1))) // range [j + 2^(i-1), j + 2^i - 1]
						);
			}
		}
	}

	[[nodiscard]] T query(std::size_t l, const std::size_t r) const {
		// we assume that l < r
		if constexpr (IDEMPOTENT) {
			// as this operation is idempotent, there is no need to carefully
			// select the items, we just pick the two ranges that might overlap,
			// but which cover the whole array 
			std::size_t i = static_cast<std::size_t>(std::bit_width(r-l+1) - 1);
			return func_(data_.get(i, l), data_.get(i, r- (static_cast<std::size_t>(1) << i) + 1));
		} else {
			std::size_t i = maxK_+1;
			// We need the first hit here.
			for (; 0 < i; i--) {
				const auto ii = i-1;
				// If we can fit the size.
				if ((static_cast<std::size_t>(1) << ii) <= r - l + 1) {
					break;
				}
			}

			if (i == 0)
				throw std::runtime_error("we couldn't find a query range?");

			T ans = data_.get(i-1, l);
			l += (1 << (i-1));
	
			// decrement ones, as we have already done this.
			i--;
			// Now we repeat the pattern, for the rest.
			for (; 0 < i; i--) {
				const auto ii = i-1;
				if ((static_cast<std::size_t>(1) << ii) <= r - l + 1) {
					ans = func_(ans, data_.get(ii, l));
					l += (1 << ii);
				}
			}

			return ans;
		}
	}
};

// A SqrtDecomp with a fixed BlockSize. Is most cases, this is going
// to be more efficient than the dynamic StaticSqrtDecomp
// 
template<typename IN, typename OUT, std::size_t BlockSize, typename F, OUT InitValue>
class StaticSqrtDecomp {
private:
	F func_{};

	std::vector<IN> orig_;
	std::vector<OUT> blocks_;


	void recompute() {
		blocks_.resize(orig_.size() / BlockSize + 1);
		std::fill(blocks_.begin(), blocks_.end(), InitValue);

		for (std::size_t i = 0; i < orig_.size(); i++) {
			blocks_[i / BlockSize] = func_(blocks_[i / BlockSize], orig_[i]);
		}
	}
	
	// This does an update on the whole range, but there are functions we can use
	// that just adjust the range. I have to think about about how we are going
	// to do that.
	void recompute(std::size_t block) {
		blocks_[block] = InitValue;
		for (std::size_t i = block*BlockSize; i < (block+1)*BlockSize; i++)
			blocks_[block] = func_(blocks_[block], orig_[i]);
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
		orig_[i] = val;
		recompute(i / BlockSize);
	}
};


void solveWithSparseTable() {
	UT N = 0;
	UT Q = 0;
	std::cin >> N >> Q;

	std::vector<UT> in(N);
	for (UT i = 0; i < N; i++)
		std::cin >> in[i];

	auto f = [](UT a, UT b) { return std::min(a, b); };
	SparseTable<UT, decltype(f), true> st(N+1);

	st.precompute(in.begin(), in.end());

	for (UT i = 0; i < Q; i++) {
		UT l = 0; UT r = 0;
		std::cin >> l >> r;
		std::cout << st.query(l-1, r-1) << std::endl;
	}
}

void solveWithSqrtDecomp() {
	UT N = 0;
	UT Q = 0;
	std::cin >> N >> Q;

	std::vector<UT> in(N);
	for (UT i = 0; i < N; i++)
		std::cin >> in[i];

	auto f = [](UT a, UT b) { return std::min(a, b); };
	/* StaticSqrtDecomp<UT, UT, 450, decltype(f), std::numeric_limits<UT>::max()> st(std::move(in)); */
	// We could get away with 448 here, but we choose 512, as it makes the compiler emit more
	// effective instructions.
	StaticSqrtDecomp<UT, UT, 512, decltype(f), std::numeric_limits<UT>::max()> st(std::move(in));

	for (UT i = 0; i < Q; i++) {
		UT l = 0; UT r = 0;
		std::cin >> l >> r;
		std::cout << st.query(l-1, r-1) << std::endl;
	}
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	/* solveWithSparseTable(); */
	solveWithSqrtDecomp();

	return 0;
}
