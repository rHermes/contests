#pragma once

#include <vector>
#include <type_traits>
#include <algorithm>

// This is a static version of the 
template<
 typename IN, // The types of the input array
 typename OUT, // The output type.
 std::size_t BlockSize, // The blocksize we will use.
 typename F, // The reduce function of form: f(ACC, CUR)
 OUT InitValue, typename DIFF_F = int>
class StaticSqrtDecomp {
	static_assert(std::is_invocable_r_v<OUT, F, OUT, IN>);
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
