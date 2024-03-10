/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */
#include <vector>

class MountainArray {
	public:
		int get(int index) { return index; };
		int length() { return 42; };
};

class Solution {
	public:
		int findInMountainArray(int target, MountainArray &mountainArr) {
			const int N = mountainArr.length();
			std::vector<int> cache(static_cast<std::size_t>(N), -1);
			int asked = 0;

			auto getCached = [&](int i) {
				const auto ii = static_cast<unsigned>(i);
				if (cache[ii] != -1)
					return cache[ii];

				asked++;
				cache[ii] = mountainArr.get(i);
				return cache[ii];
			};

			// The length is at most 1000, if we knew the i, then we could find the
			// answer in max 2*log2(1000) = ca 20.
			// 
			// This leaves us about 80 guesses to find the center.
			// We do a binary search, but at each point, we have to do 3 guesses.
			// so for 3*log2(1000) = 30 ish. This should work. Let's see.

			// Furthermore, we can just cache the answers we already have, so that
			// we don't ask twice.
			int L = 0;
			int R = N-1;

			while (L+1<R) {
				int C = (R+L) / 2;

				int cc = getCached(C);
				int cl = getCached(C-1);
				int cr = getCached(C+1);

				if (cl < cc && cc > cr) {
					// We know we have the middle now.
					L = C;
					break;
				}
				else if (cl < cc) {
					// the slop is going to the right, so we must update left.
					L = C;
				} else {
					R = C;
				}

				// Now just need to know if it slops left or right.
			}

			const int top = L;
			const int topHeight = getCached(top);
			if (target == topHeight) {
				return top;
			} else if (topHeight < target) {
				return -1;
			}

			// We search on the left side.
			const int leftHeight = getCached(0);
			if (leftHeight == target)
				return 0;

			if (leftHeight < target) {
				// We search.
				L = 0;
				R = top;
				while (L+1 < R) {
					const int C = (R+L)/2;
					int cc = getCached(C);

					if (cc == target) {
						return C;
					} else if (target < cc) {
						R = C;
					} else {
						L = C;
					}
				}

				if (getCached(L) == target) {
					return L;
				}
			}

			// We search on the right side
			const int rightHeight = getCached(N-1);
			if (rightHeight == target)
				return N-1;

			if (rightHeight < target) {
				L = top;
				R = N-1;

				while (L+1<R) {
					const int C = (R+L) / 2;
					int cc = getCached(C);

					if (cc == target) {
						return C;
					} else if (cc < target) {
						R = C;
					} else {
						L = C;
					}
				}

				if (getCached(R) == target) {
					return R;
				}
			}

			return -1;
		}
};

int main() {
	return 0;
};
