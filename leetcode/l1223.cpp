#include <vector>
#include <cstdint>
#include <array>

class Solution {
public:
	int dieSimulator(int n, std::vector<int>& rollMax) {
		using T = std::int64_t;
		constexpr T COLS = 15;
		constexpr T MODN = 1000000007;

		// This keeps track of how many ways we can eter the
		std::array<T, 6 * COLS> prev{};
		for (int i = 0; i < 6; i++) {
			prev[i * COLS] = 1;
		}

		for (int i = 1; i < n; i++) {
			std::array<T, 6 * COLS> next{};

			std::array<T, 6> prevSums{};
			T totalSum = 0;
			for (int num = 0; num < 6; num++) {
				for (int col = 0; col < COLS; col++) {
					prevSums[num] += prev[num * COLS + col];
				}
				totalSum += prevSums[num];
				prevSums[num] %= MODN;
			}

			// ok, now then, we must go for each number.
			for (int nextNum = 0; nextNum < 6; nextNum++) {
				// ok, so how many ways can we come into this with
				// 0 consecutive i.
				next[nextNum * COLS] = (totalSum - prevSums[nextNum]) % MODN;

				// ok, we have now shown how many ways we can get here from the
				// others. now we just need to see how many we can get here.
				for (int col = 1; col < rollMax[nextNum]; col++) {
					next[nextNum * COLS + col] = prev[nextNum * COLS + col - 1];
				}
			}

			prev = std::move(next);
		}

		// At the end now, the answer is simply the sum of all the prevs;
		int answer = 0;
		for (const auto c : prev) {
			answer = (answer + c) % MODN;
		}

		return answer;
	}
};

int main() { return 0; }
