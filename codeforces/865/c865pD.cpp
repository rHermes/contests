
/* constexpr UT MAX_N = 300000; */

/* #pragma once */
/* #include <functional> */

// An idea here, is to always, sell an item against the highest it
// can be sold against, if we do chose to sell it.

#include <cstdio>
#include <vector>
#include <cinttypes>
#include <queue>
#include <limits>
#include <optional>
#include <unordered_map>
#include <map>
#include <set>

using UT = std::uint64_t;
using ST = std::int64_t;

struct Key {
	UT day;
	UT shares;

	friend auto operator<=>(const Key&, const Key&) = default;
};

// We can switch this later to unordered_map
std::map<Key, std::optional<ST>> CACHE;

// This answers how much you could earn if you started on a day, given
// the nodes. It's slow now, but we want to make it easier.
std::optional<ST> solveDP(
		const std::vector<ST>& price, const std::vector<ST>& largestAfter,
		const UT day, const UT shares) {
	const UT N = price.size();

	if (day == N && shares == 0)
		return 0;
	
	// We return this, so the option will never be picked.
	if (N <= day)
		return std::nullopt;
	
	// There is not enough days to sell of all the shares, so we just exit early.
	if ((N - day) < shares)
		return std::nullopt;

	const Key key{day, shares};
	if (auto it = CACHE.find(key); it != CACHE.end())
		return it->second;

	/* printf("Called with %lu, %lu\n", day, shares); */
	const ST C = price[day];


	// Don't do anything.
	if (0 < shares) {
		// We can sell
		auto ans = solveDP(price, largestAfter, day+1, shares-1);
		if (!ans) {
			CACHE.emplace(key, std::nullopt);
			return std::nullopt;
		}

		ans = *ans + C;

		auto opt2 = solveDP(price, largestAfter, day+1, shares);
		if (opt2) {
			ans = std::max(*ans, *opt2);

			// This is a bit of a meme, but if we cannot solve it by not
			// doing anything in this spot, then we cannot solve it buy buying either.

			// There is no point buying, if there are no bigger elements in the back of the list.
			if (C < largestAfter[day]) {
				auto opt3 = solveDP(price, largestAfter, day+1, shares+1);
				if (opt3)
					ans = std::max(*ans, *opt3 - C);
			} else {
				printf("Smart skip at day %lu\n", day);
			}
		}

		CACHE.emplace(key, ans);
		return ans;
	} else {
		// we cannot sell
		// Can we solveDP it with just doing nothing here?
		auto ans = solveDP(price, largestAfter, day+1, shares);
		if (!ans) {
			CACHE.emplace(key, ans);
			return std::nullopt;
		}

		// There is no point buying, if there are no bigger elements in the back of the list.
		if (C < largestAfter[day]) {
			auto opt2 = solveDP(price, largestAfter, day+1, shares+1);
			if (opt2)
				ans = std::max(*ans, *opt2 - C);
		}

		CACHE.emplace(key, ans);
		return ans;
	}
}

struct Node {
	ST score{0};
	UT day{0};
	UT shares{0};

	/* Node(ST scor, UT d, UT sh) : score{scor}, day{d}, shares{sh} {} */
	Node(ST scor, UT d, UT sh) {
		// Not doing this in initializer, to make it easier to reorder without getting warnings.
		score = scor;
		day = d;
		shares = sh;
	}

	friend constexpr std::strong_ordering operator<=>(const Node& l, const Node& r) {
		/* if (l.score == r.score) { */
		/* 	if (l.shares == r.shares) { */
		/* 		return l.day<=>r.day; */
		/* 	} else { */
		/* 		return l.shares<=>r.shares; */
		/* 	} */
		/* } else { */
		/* 	return l.score<=>r.score; */
		/* } */

		// This is day by day sorting.
		if (l.day == r.day) {
			if (l.score == r.score) {
				return l.shares<=>r.shares;
			} else {
				return l.score<=>r.score;
			}
		} else {
			return r.day<=>l.day;
		}
	}
};

ST solveDij(const std::vector<ST>& price, const std::vector<ST>& largestAfter) {
	const UT N = price.size();

	std::priority_queue<Node> Q;
	Q.emplace(0, 0, 0);

	/* std::map<Key, std::optional<ST>> CACHE; */
	std::map<Key, ST> best;
	
	while (!Q.empty()) {
		const auto cur = Q.top();
		Q.pop();
		
		// check for termination
		if (cur.day == N) {
			if (cur.shares != 0)
				continue;

			/* continue; */
		} else {

			// We return this, so the option will never be picked.
			if (N <= cur.day)
				continue;

			// There is not enough days to sell of all the shares, so we just exit early.
			if ((N - cur.day) < cur.shares)
				continue;
		}
	

		const Key key{cur.day, cur.shares};
		if (auto it = best.find(key); it != best.end()) {
			if (cur.score <= it->second) {
				/* printf("we have been her ebefore with a better score\n"); */
				continue;
			} else {
				it->second = cur.score;
			}
		} else {
			best[key] = cur.score;
		}

		printf("We are at a node: Score=%ld, Day=%lu, Shares=%lu\n", cur.score, cur.day, cur.shares);
		
		const auto C = price[cur.day];
		// Can we sell?
		if (0 < cur.shares)
			Q.emplace(cur.score + C, cur.day+1, cur.shares-1);
		
		// Maybe we buy?
		if (C < largestAfter[cur.day] && (cur.shares+1) <= (N-cur.day-1)) {
			Q.emplace(cur.score - C, cur.day+1, cur.shares+1);
		}
		
		// Just advance the day.
		Q.emplace(cur.score, cur.day+1, cur.shares);
	}

	return best[{N, 0}];
}

ST solve(const std::vector<ST>& price, const std::vector<ST>& largestAfter) {
	/* return *solveDP(price, largestAfter, 0, 0); */
	return solveDij(price, largestAfter);
}

int main() {
	UT N = 0;
	scanf("%lu", &N);
	std::vector<ST> price(N);
	for (UT i = 0; i < N; i++)
		scanf("%ld", &price[i]);
	
	std::vector<ST> largestAfter(N);
	largestAfter[N-1] = 0;
	for (UT i = 0; i < N-1; i++) {
		const UT idx = N-2-i;
		largestAfter[idx] = std::max(price[idx+1], largestAfter[idx+1]);
	}
	printf("%ld\n", solve(price, largestAfter));

	return 0;
}
