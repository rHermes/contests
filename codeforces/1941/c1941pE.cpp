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

template <typename T>
class RollingMinSum {
	T ans_{std::numeric_limits<T>::max()};
	T cur_{0};
	const std::size_t cap_;
	std::vector<T> data_;
	std::size_t idx_{0};
	bool wrapped_{false};
	
	public:

	explicit RollingMinSum(std::size_t cap) : cap_{cap}, data_(cap_) {}

	[[nodiscard]] constexpr const T& ans() const {
		return ans_;
	}

	[[nodiscard]] constexpr const T& cur() const {
		return cur_;
	}

	constexpr void add(T val) {
		if (wrapped_) {
			cur_ -= data_[idx_];
		}

		cur_ += val;
		data_[idx_] = std::move(val);

		idx_++;
		if (idx_ == cap_) {
			idx_ = 0;
			wrapped_ = true;
		}
		if (wrapped_)
			ans_ = std::min(ans_, cur_);
	}
};

template <typename T>
class RollingMin {
	std::deque<std::pair<T,std::size_t>> q_;
	std::size_t removed_{0};
	std::size_t added_{0};
	const std::size_t capacity_;

	constexpr void pop() {
		if (!q_.empty() && q_.front().second == removed_)
			q_.pop_front();

		removed_++;
	}

public:
	
	explicit RollingMin(std::size_t cap) : capacity_{cap} {}

	[[nodiscard]] constexpr T& min() {
		return q_.front().first;
	}

	[[nodiscard]] constexpr const T& min() const {
		return q_.front().first;
	}

	constexpr void push(T val) {
		if (capacity_ <= added_)
			pop();

		while (!q_.empty() && val < q_.back().first)
			q_.pop_back();

		q_.emplace_back(std::move(val), added_);

		added_++;
	}

};

void solve() {
	UT N = 0;
	UT M = 0;
	UT K = 0;
	UT D = 0;
	std::cin >> N >> M >> K >> D;

	std::vector<UT> row(M);
	/* std::vector<UT> dp(M); */

	RollingMinSum<UT> ans(K);
	for (UT i = 0; i < N; i++) {
		for (UT j = 0; j < M; j++) {
			std::cin >> row[j];
			row[j]++;
		}

		// We have scanned in the row now.
		// Ok, so I want to reduce the amount of cases, to make this easier on my brain.

		// We always have supports at 0 and M-1
		if (M-1 <= D+1) {
			// We won't need any struts.
			ans.add(row[0] + row[M-1]);
			continue;
		}


		// M-1-D-1
		for (UT i = M-1-D-1; i < M-1; i++) {
			row[i] += row[M-1];
		}

		UT upperLimit = M-1-D-1;
		RollingMin<UT> mm(D+1);
		for (UT i = M-1; upperLimit <= i; i--)
			mm.push(row[i]);

		// But we also have a lower limit:
		for (UT i = upperLimit; 0 < i; i--) {
			UT ii = i-1;
			row[ii] += mm.min();
			mm.push(row[ii]);
		}

		ans.add(row[0]);
	}

	std::cout << ans.ans() << std::endl;
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
