#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	std::cin >> N;

	std::string a;
	std::cin >> a;
	/* std::cout << "[" << a << "]" << std::endl; */

	if (N < 3){
		std::cout << 0 << std::endl;
		return;
	}


	// Ok, so we have a couple of things going for us.
	// It doesn't matter which order we remove the letters.
	
	// Letters on different sides of another letter than piemap
	// can never effect each other.
	UT ans = 0;
	for (UT i = 0; i < N-2; i++) {
		if (a[i] == 'm' && a[i+1] == 'a' && a[i+2] == 'p') {
			// we need to delete one of a or p.
			// the only reason we shouldn't delete p is if there is 
			// a p after it.
			if (i+3 < N) {
				if (a[i+3] == 'p') {
					i += 2;
					ans++;
				} else {
					/* std::cout << "We are removing p at " << i+2 << " and skipping forward" << std::endl; */
					i += 2;
					ans++;
				}
			} else {
				ans++;
				break;
			}
		} else if (a[i] == 'p' && a[i+1] == 'i' && a[i+2] == 'e') {
			// only reason not to delete e is if there is an e after it.
			if (i+3 < N) {
				if (a[i+3] == 'e') {
					i += 2;
					ans++;
				} else {
					i += 2;
					ans++;
				}
			} else {
				ans++;
				break;
			}
		}
	}

	std::cout << ans << std::endl;
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
