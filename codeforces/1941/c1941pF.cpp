#include <iostream>
#include <map>
#include <limits>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <deque>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT M = 0;
	UT K = 0;
	std::cin >> N >> M >> K;

	std::vector<UT> A(N);
	std::vector<UT> D(M);
	std::vector<UT> F(K);

	for (UT i = 0; i < A.size(); i++)
		std::cin >> A[i];

	for (UT i = 0; i < M; i++) {
		std::cin >> D[i];
	}

	for (UT i = 0; i < K; i++) {
		std::cin >> F[i];
	}

	// Sort and remove duplicates.
	std::sort(D.begin(), D.end());
	D.erase(std::unique(D.begin(), D.end()), D.end());
	M = D.size();

	std::sort(F.begin(), F.end());
	F.erase(std::unique(F.begin(), F.end()), F.end());
	K = F.size();
	
	// We want to do the bineary search through the biggest array, to save time.
	if (K < M) {
		std::swap(K, M);
		std::swap(D, F);
	}
	
	// We find the largest and second largest intervals. The second largest interval
	// is the best we can ever do, as we can only ever focus on the first interval.
	UT ans2 = 0;
	UT ans = 0;
	std::vector<UT> ranges;
	for (UT i = 1; i < N; i++) {
		const auto diff = A[i] - A[i-1];
		if (ans == diff) {
			ranges.emplace_back(i);
		} else if (ans < diff) {
			ans2 = ans;
			ans = diff;
			ranges.clear();
			ranges.emplace_back(i);
		} else if (ans2 < diff) {
			ans2 = diff;
		}
	}

	// If the current answer is 1, we can never produce a better answer.
	// If there are more than range with the same size, we can never do
	// any better, as we can only affect one of them.
	if (ans == 1 || 1 < ranges.size()) {
		std::cout << ans << std::endl;
		return;
	}

	const auto upperLimit = A[ranges[0]];
	const auto lowerLimit = A[ranges[0]-1];
	std::vector<UT> targets;
	if ((upperLimit - lowerLimit) % 2 == 0) {
		targets.emplace_back((lowerLimit+upperLimit)/2);
	} else {
		targets.emplace_back((lowerLimit+upperLimit)/2);
		targets.emplace_back((lowerLimit+upperLimit)/2 + 1);
	}

	
	auto binSearch = [&](const UT idx, const UT target) {
		const UT shift = D[idx];
		if (target <= (shift+F.front()))
			return std::make_pair(shift + F.front(), shift + F.front());

		if ((shift + F.back()) <= target) {
			return std::make_pair(shift + F.back(), shift + F.back());
		}

		UT L = 0;
		UT R = K-1;
		while (L+1<R) {
			const UT C = (L+R)/2;
			const UT Cval = shift + F[C];

			if (target < Cval) {
				R = C;
			} else {
				L = C;
			}
		}

		auto Lval = F[L] +shift;
		auto Rval = F[R] +shift;
		return std::make_pair(Lval, Rval);
	};
	for (const auto& totalTarget : targets) {
		UT bestLeft = lowerLimit;
		UT bestRight = upperLimit;
		auto bestLeftAns = std::max(upperLimit - bestLeft, bestLeft - lowerLimit);
		auto bestRightAns = std::max(upperLimit - bestRight, bestRight - lowerLimit);


		/* std::cout << "We start the binary search with our best range being: [" << bestLeft << ", " << bestRight << "]" << std::endl; */
		for (UT m = 0; m < M; m++) {
			auto rg = binSearch(m, totalTarget);
			if (rg.first <= totalTarget) {
				bestLeft = std::max(bestLeft, rg.first); 
				bestLeftAns = std::max(upperLimit - bestLeft, bestLeft - lowerLimit);
			}
			if (totalTarget <= rg.second) {
				bestRight = std::min(bestRight, rg.second);
				bestRightAns = std::max(upperLimit - bestRight, bestRight - lowerLimit);
			}
		}


		ans = std::min(ans, std::min(bestLeftAns, bestRightAns));
	}
	std::cout << std::max(ans, ans2) << std::endl;
}


int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
		/* break; */
	}
}
