#include <vector>
#include <iostream>

class Solution {
	public:
		int maximalRectangle(std::vector<std::vector<char>>& matrix) {
			const auto rows = matrix.size();
			const auto cols = matrix[0].size();

			std::vector<int> height(cols);
			int ans = 0;
			// We look at the first
			for (std::size_t row = 0; row < rows; row++) {
				// first we update the height.
				for (std::size_t i = 0; i < cols; i++) {
					if (matrix[row][i] == '1') {
						height[i]++;
					} else {
						height[i] = 0;
					}
				}

				// Ok, now we find the largest rectangle in this histogram.
				for (std::size_t i = 0; i < cols; i++) {
					auto h = height[i];
					auto j = i+1;
					for (; j < cols; j++) {
						const auto hj = height[j];
						if (h <= hj)
							continue;


						// ok, so this is the end of the road, for this height, but we can continue
						// going with the new one, given it's not 0.
						if (hj == 0)
							break;

						// ok, now we calculate the current answer, and then we go one lower.
						ans = std::max(ans, h * static_cast<int>(j-i));
						h = hj;   
					}
					ans = std::max(ans, h * static_cast<int>(j - i));
				}
			}

			return ans;
		}
};

int main() {
}
