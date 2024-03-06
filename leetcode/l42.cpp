#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

int trap(std::vector<int>& height) {
	const auto N = height.size();
	
	// we want a well formed range, which starts end ends with a bar.
	std::size_t left = 0;
	while (left < N && height[left] == 0)
		left++;

	if (left == N)
		return 0;

	std::size_t right = N-1;
	while ((left+1) < right && height[right] == 0)
		right--;

	if (left == right || left+1 == right)
		return 0;

	std::vector<std::size_t> biggestPeaks;
	int maxHeight = 1;

	for (auto i = left; i <= right; i++) {
		auto hh = height[i];
		if (maxHeight < hh) {
			maxHeight = hh;
			biggestPeaks.clear();
			biggestPeaks.emplace_back(i);

		} else if (hh == maxHeight) {
			biggestPeaks.push_back(i);
		}
	}

	// ok, now we merge the peaks.
	auto& peaks = biggestPeaks;
	auto peakHeight = maxHeight;

	int ans = 0;
	// we assert that the prevBiggestPeaks must always be atleast 2, since we have
	// a beinning and a start.
	for (std::size_t i = 0; i < peaks.size()-1; i++) {
		auto cur = peaks[i];
		auto next = peaks[i+1];
		/* std::cout << "We have peaks: " << cur << " and " << next << std::endl; */

		ans += static_cast<int>(next-cur-1)*peakHeight;
		// We remove the peaks between.
		for (std::size_t j = cur+1; j < next; j++) {
			ans -= height[j];
		}
	}

	// of now for the right side of the peaks.
	// From the left, we just add the amount of water that can be held above us, at the current moment.
	auto currentBestHeight = height[left];
	for (auto i = left+1; i < peaks[0]; i++) {
		if (height[i] < currentBestHeight) {
			ans += (currentBestHeight - height[i]);
		} else {
			currentBestHeight = height[i];
		}
	}

	// now we just need to do the opposite for the right peak
	currentBestHeight = height[right];
	for (auto i = right; peaks.back() < i; i--) {
		if (height[i] < currentBestHeight) {
			ans += (currentBestHeight - height[i]);
		} else {
			currentBestHeight = height[i];
		}
	}

	return ans;
}

int main() {
	std::vector<int> t1 = {0,1,0,2,1,0,1,3,2,1,2,1};
	/* std::vector<int> t1 = {0}; */
	std::cout << trap(t1) << std::endl;
	return 0;
}
