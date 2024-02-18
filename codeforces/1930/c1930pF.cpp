#include <cstdio>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <array>
#include <cinttypes>
#include <algorithm>
#include <memory>
#include <numeric>
#include <bit>

// Because codeforces has a different view of this.
#define SCU "%" SCNu32 " "
#define PRU "%" PRIu32

using UT = std::uint32_t;                                                                                                                             

class Solver {
	private:
		UT maxAns_{0};
		UT inversionFilter_{0};

		std::array<std::vector<bool>, 2> sets_{};

		void updateSet(const bool idx, const UT mask) {
			if (sets_[idx][mask])
				return;

			sets_[idx][mask] = true;
			if (sets_[0][mask] && sets_[1][mask]) {
				maxAns_ = std::max(maxAns_, mask);
			}
		
			// We will only change the bits that are set. We use count leading zeros
			// to identify which bits are set, without having to iteratore through all
			// of them.
			UT ourMask = mask;
			while (0 < ourMask) { 
				const auto leadingZeros = std::countl_zero(ourMask);
				const UT filter = 1<<(31-leadingZeros);
				
				if (!sets_[idx][mask^filter])
					updateSet(idx, mask ^ filter);

				ourMask ^= filter;
			}
		}

	public:

		explicit Solver(UT n) {
			// This will create a filter we we will use to negate the values later,
			// without also setting all the bits which will be identical for all
			// values.
			inversionFilter_ = (std::bit_floor(n)<<1) - 1;
			sets_[0].resize(inversionFilter_+1);
			sets_[1].resize(inversionFilter_+1);
		}

		
		void addNumber(const UT val) {
			updateSet(0, val);
			updateSet(1, val^inversionFilter_);
		}

		[[nodiscard]] UT currentAnswer() const {
			return maxAns_;
		}
};

void solve() {
	UT N = 0;
	UT Q = 0;
	scanf(SCU, &N);
	scanf(SCU, &Q);

	Solver sol(N);

	UT lastOutput = 0;
	for (UT i = 0; i < Q; i++) {
		UT ei = 0;
		scanf(SCU, &ei);
		const UT v = (ei + lastOutput) % N;

		sol.addNumber(v);
		lastOutput = sol.currentAnswer();
		printf(PRU " ", lastOutput);
	}
	printf("\n");
}


int main() {
	UT T = 0;
	scanf(SCU, &T);
	for (UT t = 0; t < T; t++) {
		solve();
	}

	return 0;
}
