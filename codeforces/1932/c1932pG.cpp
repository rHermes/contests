#include <iostream>
#include <vector>
#include <cinttypes>
#include <queue>
#include <set>
#include <numeric>

using ST = std::int64_t;
using UT = std::uint64_t;


// Taken from wikipedia, extended euclidiean algorithm
ST modInverse(const ST a, const ST MOD) {
	ST t = 0;
	ST r = MOD;
	ST newt = 1;
	ST newr = ((a % MOD) + MOD) % MOD;

	while (newr != 0) {
		ST quot = r / newr;
		auto oldt = t;
		t = newt;
		newt = oldt - quot * newt;

		auto oldr = r;
		r = newr;
		newr = oldr - quot * newr;
	}

	if (1 < r)
		return -1;
	if (t < 0)
		t += MOD;

	return t;
}

void solve() {
	UT N = 0;
	UT M = 0;
	ST H = 0;
	std::cin >> N >> M >> H;

	std::vector<ST> L(N);
	for (UT i = 0; i < N; i++)
		std::cin >> L[i];

	std::vector<ST> S(N);
	for (UT i = 0; i < N; i++)
		std::cin >> S[i];

	std::vector<std::vector<UT>> G(N);
	for (UT i = 0; i < M; i++) {
		UT a = 0;
		UT b = 0;
		std::cin >> a >> b;
		G[a-1].emplace_back(b-1);
		G[b-1].emplace_back(a-1);
	}
	
	// Current step, position
	std::set<UT> seen;
	using P = std::pair<UT,UT>;
	std::priority_queue<P, std::vector<P>, std::greater<P>> Q;
	Q.emplace(0,0);

	while (!Q.empty()) {
		auto [score, cur] = Q.top();
		Q.pop();

		if (cur == N-1) {
			// It's adding one, because we are not thinking we started on one.
			std::cout << score + 1<< std::endl;
			return;
		}

		if (auto it = seen.insert(cur); !it.second)
			continue;

		const ST la = (L[cur] + ((static_cast<ST>(score) % H)*S[cur]) % H) % H;
		for (const auto& next : G[cur]) {
			if (seen.count(next))
				continue;

			const ST lb = (L[next] + ((static_cast<ST>(score) % H)*S[next]) % H) % H;

			if (la == lb) {
				Q.emplace(score, next);
				continue;
			}
			
			// La and lb doesn't match and we have the same steps, so we 
			// can never meet.
			if (S[next] == S[cur])
				continue;
				

			const ST leftSide = ((S[cur] - S[next]) % H + H) % H;
			const ST rightSide = ((lb- la) % H + H) % H;

			const ST d = std::gcd(leftSide, H);
			if (d != 1) {
				if (rightSide % d != 0)
					continue;
				
				const ST Hn = H / d;
				const ST inv = modInverse(leftSide / d, Hn);
				if (inv < 0) {
					throw std::exception();
				}
				ST Xn = (inv * (rightSide/d)) % Hn;

				ST bestX = Xn;
				for (ST i = 1; i < d; i++) {
					Xn = (Xn + Hn) % H;
					bestX = std::min(bestX, Xn);
				}

				const ST calcedNextLeft = (la + S[cur]*bestX) % H;
				const ST calcedNextRight = (lb + S[next]*bestX) % H;
				if (calcedNextLeft != calcedNextRight) {
					printf("The inputs are %ld %ld %ld %ld\n", la, lb, S[cur], S[next]);
					return;
				}

				Q.emplace(score + static_cast<UT>(bestX), next);
			} else {
				// We now check to see if we can solve this at all
				const ST inv = modInverse(leftSide, H);
				if (inv < 0) {
					throw std::exception();
				}
				ST stepsNeeded = (inv * rightSide) % H;
				if (stepsNeeded < 0)
					stepsNeeded += H;

				const ST calcedNextLeft = (la + S[cur]*stepsNeeded) % H;
				const ST calcedNextRight = (lb + S[next]*stepsNeeded) % H;
				if (calcedNextLeft != calcedNextRight) {
					printf("The inputs are %ld %ld %ld %ld\n", la, lb, S[cur], S[next]);
					return;
				}

				Q.emplace(score + static_cast<UT>(stepsNeeded), next);
			}

		}
	}
	
	// If we reach here, we have not found any other solution.
	std::cout << "-1" << std::endl;
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);
	std::cin.exceptions(std::cin.badbit);

	UT T = 0;
	std::cin >> T;
	for (UT t = 0; t < T; t++) {
		solve();
	}
}
