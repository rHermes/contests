#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT K = 0;
	std::cin >> N >> K;
	
	std::vector<UT> A(N);
	for (UT i = 0; i < N; i++)
		std::cin >> A[i];

	std::vector<UT> B(N);
	for (UT i = 0; i < N; i++)
		std::cin >> B[i];


	std::vector<UT> outA; outA.reserve(2*K);
	std::vector<UT> outB; outB.reserve(2*K);
	std::vector<UT> singleA; 

	std::sort(A.begin(), A.end());
	for (UT i = 0; i < N && outA.size() < 2*K; i++) {
		if (i < N-1 && A[i] == A[i+1]) {
			outA.emplace_back(A[i]);
			outA.emplace_back(A[i]);
			i++;
		} else {
			singleA.push_back(A[i]);
		}
	}

	while (outA.size() < 2*K) {
		outA.push_back(singleA.back());
		outB.push_back(singleA.back());
		singleA.pop_back();
	}


	std::sort(B.begin(), B.end());
	for (UT i = 1; i < N && outB.size() < 2*K; i++) {
		if (B[i] == B[i-1]) {
			outB.emplace_back(B[i]);
			outB.emplace_back(B[i]);
			i++;
		}
	}

	for (const auto& p : outA) {
		std::cout << p << " ";
	}
	std::cout << '\n';
	for (const auto& p : outB) {
		std::cout << p << " ";
	}
	std::cout << '\n';
}

int main() {
	std::cin.tie(nullptr);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
