#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

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

	// ok, so we have to pick two sets of size 2*k.
	// This really just means we can pick any combination
	// we want of the items in both.
	
	/* std::sort(A.begin(), A.end()); */
	/* std::sort(B.begin(), B.end()); */

	std::unordered_map<UT,UT> mapA;
	for (const auto p : A)
		mapA[p] += 1;

	std::unordered_map<UT,UT> mapB;
	for (const auto& p : B)
		mapB[p] += 1;

	/* std::cout << "WEW" << std::endl; */
	/* for (const auto& p : mapA) */
	/* 	std::cout << p.first << " " << p.second << std::endl; */
	/* std::cout << "WOW" << std::endl; */
	

	std::vector<UT> outA;
	std::vector<UT> outB;
	
	{
		auto it = mapA.cbegin();
		while (outA.size() < 2*K) {
			if (it->second == 2 && (outA.size()+2 <= 2*K)) {
				outA.push_back(it->first);
				outA.push_back(it->first);
			} else if (it->second == 1) {
				outA.push_back(it->first);
				outB.push_back(it->first);
			}

			it++;
		}
	}
	
	{
		auto it = mapB.cbegin();
		while (outB.size() < 2*K) {
			if (it->second == 2) {
				outB.push_back(it->first);
				outB.push_back(it->first);
			}
			it++;
		}
	}
	
	/* UT i = 0; */
	/* while ( outA.size() < 2*K ) { */
	/* 	if (outA.size()+2 <= 2*K) { */
	/* 		if (i < N-1) { */
	/* 			if (A[i] == A[i+1]) { */
	/* 				outA.push_back(A[i]); */
	/* 				outA.push_back(A[i]); */
	/* 				i += 2; */
	/* 			} else { */
	/* 				outA.push_back(A[i]); */
	/* 				outB.push_back(A[i]); */
	/* 				i += 1; */
	/* 			} */
	/* 		} else { */
	/* 			throw std::runtime_error("We are not supposed to be here!"); */
	/* 		} */
	/* 	} else { */
	/* 		if (i < N-1) { */
	/* 			if (A[i] != A[i+1]) { */
	/* 				outA.push_back(A[i]); */
	/* 				outB.push_back(A[i]); */
	/* 				i += 1; */
	/* 			} else { */
	/* 				i += 2; */
	/* 			} */
	/* 		} else { */
	/* 			outA.push_back(A[i]); */
	/* 			outB.push_back(A[i]); */
	/* 			i += 1; */
	/* 		} */
	/* 	} */
	/* } */

	/* i = 0; */
	/* while (outB.size() < 2*K) { */
	/* 	// We only add doubles here. */
	/* 	if (B[i] == B[i+1]) { */
	/* 		outB.push_back(B[i]); */
	/* 		outB.push_back(B[i]); */
	/* 		i += 2; */
	/* 	} else { */
	/* 		i += 1; */
	/* 	} */
	/* } */

	for (const auto& p : outA) {
		std::cout << p << " ";
	}
	std::cout << std::endl;
	for (const auto& p : outB) {
		std::cout << p << " ";
	}
	std::cout << std::endl;
}

int main() {
	/* std::cin.tie(nullptr); */
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
