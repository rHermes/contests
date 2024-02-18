#include <string>
#include <cstdio>
#include <vector>
#include <cinttypes>
#include <deque>

// Because codeforces has a different view of this.
#define SCU "%" SCNu64 " "
#define SCD "%" SCNd64 " "
#define PRU "%" PRIu64
#define PRD "%" PRId64

using UT = std::uint64_t;
using ST = std::int64_t;


int main() {
	UT T = 0;
	scanf(SCU, &T);

	for (UT t = 0; t < T; t++) {
		UT N = 0;
		UT M = 0;
		scanf(SCU, &N);
		scanf(SCU, &M);
		std::vector<UT> a(N);


		for (UT i = 0; i < N; i++) {
			scanf(SCU, &a[i]);
		}
		
		// We track which is removed at each step.
		std::vector<UT> rem;
		UT L = 0;
		UT R = N-1;
		for (UT i = 0; i < N; i++) {
			int c = getc(stdin);
			if (c == 'L') {
				rem.push_back(a[L]);
				L++;
			}
			else if (c == 'R') {
				rem.push_back(a[R]);
				R--;
			}
			else
				throw std::exception();
		}
	
		std::vector<UT> ans;
		for (auto it = rem.rbegin(); it != rem.rend(); it++) {
			UT prev = 1;
			if (!ans.empty())
				prev = ans.back();

			prev = (prev * (*it)) % M;
			ans.push_back(prev);
		}

		for (auto it = ans.crbegin(); it != ans.crend(); it++)
			printf(PRU " ", *it);

		printf("\n");
	}
	return 0;
}
