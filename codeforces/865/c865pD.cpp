/**
 * MemSQL Start[c]UP 3.0 Round 2 - D. Buy Low Sell High
 *
 * I had to read the editorial to solve this one, but the solution is very
 * elegant. We view each price as an option to buy it at that price. We don't
 * actually cash out on it, but wait for a price that is lower than it.
 *
 * At this point, we know that we are going to be exercising that option
 * or one that is cheaper than it. The question is more, when should we actually
 * cash out the option? This is the crux of the problem, we don't really have
 * to think about when, because we can simply sell now, and add the current
 * price as an option. This is because the options are transitive.
 *
 * We buy the first option for A, the price of today is B. We earn B-A and
 * we add B to the list of options. We then come to C, which is even larger.
 * We sell B now then and we earn C-B.
 *
 * Now our total earnings is B-A + C-B = C-A, which is the same as if we
 * would have waited to sell A. It's important to note here, that adding
 * the current price to the options list when we cash out another option,
 * comes in addition to adding today's option.
 */
#include <cstdio>
#include <vector>
#include <cinttypes>
#include <queue>

using UT = std::uint64_t;

int main() {
	UT N = 0;
	scanf("%lu", &N);

	UT ans = 0;
	std::priority_queue<UT,std::vector<UT>,std::greater<UT>> options;

	for (UT i = 0; i < N; i++) {
		UT price = 0;
		scanf("%lu", &price);

		if (!options.empty() && options.top() < price) {
			ans += price - options.top();
			options.pop();
			options.emplace(price);
		}

		options.emplace(price);
	}

	printf("%" PRIu64 "\n", ans);
	return 0;
}
